#include "EventLoop.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include <unistd.h>
#include <sys/eventfd.h>
#include <iostream>

using std::cout;
using std::endl;

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtList()
, _isLooping(false)
, _acceptor(acceptor)
, _evtfd(createEventFd())
, _mutex()
{
    _evtList.reserve(1024);
    //监听listenfd
    int listenfd = _acceptor.fd();
    addEpollReadFd(listenfd);
    //监听用于通信的文件描述符
    addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
    close(_evtfd);
}

//是否在循环
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    _isLooping = false;
}

//封装epoll_wait的函数
void EventLoop::waitEpollFd()
{
    int nready = 0;
    do
    {
        //第二个是struct结构体，
        //先从vector<struct epoll_event>_evtList的开始取出第一个元素(就是*)
        //然后再使用&取地址得到的就是首地址,vector的size就是epoll_event最大元素个数
        nready = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    //这里使用dowhile代替了原来的continue跳过这次循环
    }while(-1 == nready && errno == EINTR);

    if(-1 == nready)
    {
        std::cerror << "-1 == nready" << endl;
        return;
    }
    else if(0 == nready)
    {
        //打印超时
        cout << ">>epoll_wait timeout!!!" << endl;
    }
    else
    {
        //需要考虑vector存不下满足条件的文件描述符
        //所以需要扩容vector
        if((int)_evtList.size() == nready)
        {
            _evtList.resize(2 * nready);
        }

        for(int idx = 0; idx < nready; ++idx)
        {
            int listenfd = _acceptor.fd();
            int fd = _evtList[idx].data.fd;
            if(listenfd == fd)
            {
                //有新的连接请求上来
                handleNewConnection();
            }
            else if(fd == _evtfd)
            {
                handleRead();
                //此处的"任务"只是线程池处理之后的msg吗？
                doPengdingFunctors();//执行所有的"任务"
            }
            else
            {
                //connfd就绪了
                handleMessage(fd);
            }
        }
    }
}

//处理新的连接
void EventLoop::handleNewConnection()
{
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }
    //将connfd放在红黑树上进行监听
    addEpollReadFd(connfd);

    //创建TcpConnection对象
    /* TcpConnection con(connfd); */
    TcpConnectionPtr con(new TcpConnection(connfd, this));

    //三个之间通过EventLoop中转，然后交给了TcpConnection连接
    con->setNewConnectionCallback(_onNewConnection);
    con->setCloseCallback(_onClose);
    con->setMessageCallback(_onMessage);

    //将文件描述符与连接的对象存放在map中
    _conns[connfd] = con;

    con->handleNewConnectionCallback();//回调连接建立的事件
}

//处理消息的收发
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        //判断对端是否已经关闭了
        bool flag = it->second->isClosed();
        if(flag)
        {
            //处理连接断开的事件
            it->second->handleCloseCallback();
            delEpollReadFd(fd);//将文件描述符从红黑树上删除
            _conns.erase(it);//将文件描述符与对应的连接从map中删除
        }
        else
        {
            //处理消息到达的事件
            it->second->handleMessageCallback();
        }
        /* string msg = it->second->receive(); */
        /* cout << ">>recv msg from client: " << msg << endl; */
        //msg是客户端传递给服务器的数据
        //应该根据具体的业务逻辑做处理

        /* it->second->send(msg); */
    }
    else
    {
        cout << "该连接不存在 " << endl;
        return;
    }
}

//创建epfd
int EventLoop::createEpollFd()
{
    int fd = epoll_create1(0);
    if(fd < 0)
    {
        perror("createEpollFd");
        return fd;
    }
    return fd;
}

//监听文件描述符
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(ret < 0)
    {
        perror("epoll_ctl add");
        return;
    }
}

//取消监听文件描述符
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0)
    {
        perror("epoll_ctl del");
        return;
    }

}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onNewConnection = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onClose = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessage = std::move(cb);
}

//创建用于通信的文件描述符
int EventLoop::createEventFd()
{
    int ret = eventfd(10, 0);
    if(ret < 0)
    {
        perror("eventfd");
        return ret;
    }
    return ret;
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("handleRead");
        return;
    }
}
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("wakeup");
        return;
    }
}

//遍历vector，将其中所有的任务进行执行
void EventLoop::doPengdingFunctors()
{
    vector<Functor> tmp;
    {
        std::lock_guard<mutex> lg(_mutex);
        tmp.swap(_pendings);
    }

    for(auto &cb : tmp)
    {
        cb();//到底在做什么东西
    }
}

void EventLoop::runInLoop(Functor &&cb)
{
    //多个线程互斥访问vector这个共享资源，所以加锁
    //控制锁的粒度
    {
        std::lock_guard<mutex> lg(_mutex);
        _pendings.push_back(std::move(cb));
    }

    //只要“任务”存放到了EventLoop中了，就可以唤醒Reactor发数据了
    wakeup();
}

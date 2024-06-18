#include "EventLoop.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtList(1024)
, _isLooping(false)
, _acceptor(acceptor)
{
    //监听listenfd
    int listenfd = _acceptor.fd();
    addEpollReadFd(listenfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
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
        nready = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    }while(-1 == nready && errno == EINTR);

    if(-1 == nready)
    {
        cout << "-1 == nready" << endl;
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
    TcpConnectionPtr con(new TcpConnection(connfd));

    //将文件描述符与连接的对象存放在map中
    _conns[connfd] = con;
}

//处理消息的收发
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        string msg = it->second->receive();
        cout << ">>recv msg from client: " << msg << endl;
        //msg是客户端传递给服务器的数据
        //应该根据具体的业务逻辑做处理

        it->second->send(msg);
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

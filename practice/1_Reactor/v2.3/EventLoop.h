#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

class Acceptor;//前向声明
class TcpConnection;//前向声明

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;

class EventLoop
{
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    //是否在循环
    void loop();
    void unloop();
private:
    //封装epoll_wait的函数
    void waitEpollFd();

    //处理新的连接
    void handleNewConnection();
    //处理消息的收发
    void handleMessage(int fd);

    //创建epfd
    int createEpollFd();

    //监听文件描述符
    void addEpollReadFd(int fd);

    //取消监听文件描述符
    void delEpollReadFd(int fd);

public:
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);

private:
    int _epfd;//通过epoll_create创建的文件描述符
    vector<struct epoll_event> _evtList;//用于存放就绪的文件描述符的集合
    bool _isLooping;//标识是否在循环
    Acceptor &_acceptor;//获取连接器的对象的引用
    map<int, TcpConnectionPtr> _conns;//存在文件描述符与连接的键值对

    TcpConnectionCallback _onNewConnection;//连接建立的事件
    TcpConnectionCallback _onClose;//连接断开的事件
    TcpConnectionCallback _onMessage;//消息到达的事件

};

#endif

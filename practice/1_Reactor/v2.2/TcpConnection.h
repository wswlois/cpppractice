#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"

#include <memory>
#include <functional>

using std::shared_ptr;
using std::function;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string &msg);
    string receive();
    bool isClosed() const;

    //为了方便调试的函数
    string toString();

private:
    //获取本端地址与对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

public:
    //注册三个事件
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);

    //执行三个事件
    void handleNewConnectionCallback();
    void handleCloseCallback();
    void handleMessageCallback();

private:
    SocketIO _sockIO;

    //为了调试而加入的三个数据成员
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onNewConnection;//连接建立的事件
    TcpConnectionCallback _onClose;//连接断开的事件
    TcpConnectionCallback _onMessage;//消息到达的事件
};

#endif

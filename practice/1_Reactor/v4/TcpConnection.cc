#include "TcpConnection.h"
#include "EventLoop.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd, EventLoop *loop)
: _loop(loop)
, _sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string &msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

//这个函数里面到底需要实现什么东西呢？
//本质上就是将msg传递给EventLoop
//发送的“任务”是：线程池处理好之后的数据msg，以及
//要送数据的连接TcpConnection的对象，以及发送数据
//能力的函数send函数
void TcpConnection::sendToLoop(const string &msg)
{
    if(_loop)
    {
        //void runInLoop(function<void()> &&)
        _loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
    }
}

string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readLine(buff, sizeof(buff));

    return string(buff);
}

bool TcpConnection::isClosed() const
{
    //看对端是否关闭
    char buff[10] = {0};
    int ret = ::recv(_sock.fd(), buff, sizeof(buff), MSG_PEEK);
    return ret == 0;
}
string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }

    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
    }

    return InetAddress(addr);
}

//注册三个事件
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &cb)
{
    _onNewConnection =  cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onClose = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onMessage = cb;
}

//执行三个事件
void TcpConnection::handleNewConnectionCallback()
{
    if(_onNewConnection)
    {
        /* _onNewConnection(shared_ptr<TcpConnection>(this)); */
        _onNewConnection(shared_from_this());//回调
    }
    else
    {
        cout << "nullptr == _onNewConnection" << endl;
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        _onClose(shared_from_this());
    }
    else
    {
        cout << "nullptr == _onClose" << endl;
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage)
    {
        _onMessage(shared_from_this());
    }
    else
    {
        cout << "nullptr == _onMessage" << endl;
    }
}

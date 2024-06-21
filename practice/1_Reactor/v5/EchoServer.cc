#include "EchoServer.h"
#include "TcpConnection.h"
#include <iostream>

using std::cout;
using std::endl;

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con)
: _msg(msg)
, _con(con)
{

}

void MyTask::process()
{
    //这就是以后得业务逻辑处理的位置，
    //可以在此处实现
    _con->sendToLoop(_msg);
}

EchoServer::EchoServer(size_t threadNum, size_t queSize,
                       const string &ip, unsigned short port)
: _pool(threadNum, queSize)
, _server(ip, port)
{

}

EchoServer::~EchoServer()
{

}

//服务器的启动与通知
void EchoServer::start()
{
    _pool.start();
    using namespace std::placeholders;
    //function<void(EchoServer *, const TcpConnectionPtr &)>
    //-->function<void(const TcpConnectionPtr &)>
    _server.setAllCallback(std::bind(&EchoServer::onNewConnection, this, _1)
                           , std::bind(&EchoServer::onMessage, this, _1)
                           , std::bind(&EchoServer::onClose, this, _1));
    _server.start();
}

void EchoServer::stop()
{
    _pool.stop();
    _server.stop();
}

//三个回调
void EchoServer::onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!!" << endl;
}

void EchoServer::onMessage(const TcpConnectionPtr &con)
{
    string msg = con->receive();
    cout << ">>recv msg from client: " << msg << endl;
    //msg是客户端传递给服务器的数据
    //应该根据具体的业务逻辑做处理
    MyTask task(msg, con);

    _pool.addTask(std::bind(&MyTask::process, task));
}

void EchoServer::onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;

}

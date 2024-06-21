#ifndef __ECOSERVER_H__
#define __ECOSERVER_H__

#include "ThreadPool.h"
#include "TcpServer.h"

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con);
    void process();
private:
    string _msg;
    TcpConnectionPtr _con;
};

class EchoServer
{
public:
    EchoServer(size_t threadNum, size_t queSize,
               const string &ip, unsigned short port);
    ~EchoServer();

    //服务器的启动与通知
    void start();
    void stop();

    //三个回调
    void onNewConnection(const TcpConnectionPtr &con);
    void onMessage(const TcpConnectionPtr &con);
    void onClose(const TcpConnectionPtr &con);

private:
    ThreadPool _pool;//线程池对象
    TcpServer _server;//TcpServer的对象

};

#endif

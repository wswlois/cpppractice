#include "TcpServer.h"
#include "TcpConnection.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

ThreadPool *gPool = nullptr;

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con)
    : _msg(msg)
    , _con(con)
    {

    }
    void process()
    {
        _msg;
        //业务逻辑的处理在本函数
        //...
        //...
        _con->sendToLoop(_msg);
    }
private:
    string _msg;
    TcpConnectionPtr _con;
};

//连接建立
void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!!" << endl;
}

void onMessage(const TcpConnectionPtr &con)
{
    string msg = con->receive();
    cout << ">>recv msg from client: " << msg << endl;
    //msg是客户端传递给服务器的数据
    //应该根据具体的业务逻辑做处理
    MyTask task(msg, con);

    gPool->addTask(std::bind(&MyTask::process, task));
}

void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}

void test()
{
    ThreadPool pool(4, 10);
    pool.start();
    gPool = &pool;

    TcpServer server("127.0.0.1", 8888);
    server.setAllCallback(std::move(onNewConnection)
                          , std::move(onMessage)
                          , std::move(onClose));

    server.start();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


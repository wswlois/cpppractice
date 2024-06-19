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
    //注意必须要用const &左值引用，不能用右值
    //必须要拷贝，如果使用std::move会导致这个函数直接被移走
    //导致后续新的连接进来的时候进入空指针
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
    // 先建立线程池，里面阻塞在了任务部分，内部没有任务
    // 4个thread都在sleep
    ThreadPool pool(4, 10);
    pool.start();

    //全局的线程，因为在MyTask里面需要用
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


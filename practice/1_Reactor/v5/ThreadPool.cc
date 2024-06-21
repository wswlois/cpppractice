#include "ThreadPool.h"
#include <iostream>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{

}

ThreadPool::~ThreadPool()
{

}

//线程池的启动与停止
void ThreadPool::start()
{
    //创建出线程，存放在vector，同时还要将线程运行起来
    for(size_t idx = 0; idx < _threadNum; ++idx)
    {
        _threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

void ThreadPool::stop()
{
    //为了解决任务执行不完，程序就退出的问题，可以让主线程等待
    //子线程，并且是子线程任务一定要执行完之后，主线程才能继续
    //执行后面的代码
    while(!_taskQue.empty())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    _isExit = true;//标识线程池退出
    //将所有工作线程（子线程唤醒）
    /* _notEmpty.notify_all(); */
    _taskQue.wakeup();

    //线程池停止的时候，需要将所有的工作线程回收
    for(auto &th : _threads)
    {
        th.join();
    }
}

//添加任务与获取任务
void ThreadPool::addTask(Task &&task)
{
    if(task)
    {
        _taskQue.push(std::move(task));
    }
}

Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池中的工作线程需要执行的函数（线程池交给工作线程执行的任务）
//子线程在执行getTask获取到最后几个任务之后，本应该继续执行后续
//的process函数，将任务执行完毕，但是此时主线程在stop可以继续向
//下执行，也就是跳过stop函数中的while循环,如果子线程执行process
//的速率比较慢，那么有可能主线程已经将_isExit设置为了true，那么
//子线程在执行完process走到while循环的时候，发现while已经进不去
//了，那么主线程可以可以将子线程回收；如果子线程执行process的
//速率比较快，子线程再去走while循环的时候，发现主线程还没有来
//得急将标志位_isExit设置为true，那么子线程会继续进入到while
//循环中，发在已经没有任务了，所以在执行getTask的时候，就睡眠
//了
void ThreadPool::doTask()
{
    while(!_isExit)
    {
        Task taskcb = getTask();//获取任务
        if(taskcb)
        {
            taskcb();//回调函数
        }
        else
        {
            cout << "nullptr == ptask" << endl;
        }
    }
}

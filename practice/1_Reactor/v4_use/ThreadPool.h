#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <thread>
#include <functional>

using std::vector;
using std::thread;
using std::function;

using Task = function<void()>;

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    //线程池的启动与停止
    void start();
    void stop();

    //添加任务与获取任务
    void addTask(Task &&);
private:
    Task getTask();
    //线程池中的工作线程需要执行的函数（线程池交给工作线程执行的任务）
    void doTask();

private:
    size_t _threadNum;//子线程的数目
    size_t _queSize;//任务队列的大小
    vector<thread> _threads;//存放子线程的容器
    TaskQueue _taskQue;//任务队列
    bool _isExit;//标识线程是否退出的标志

};

#endif

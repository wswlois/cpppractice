#include <queue>
#include <mutex>
#include <condition_variable>

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

class Task;

class TaskQueue
{
public:
    TaskQueue(size_t capacity);
    ~TaskQueue() {}

    // 添加任务和获取任务
    void pushTask(Task *);
    Task * pop();

    // 判空还是满
    bool boolEmpty() const;
    bool boolFull() const;

    // 将所有等待在_notEmpty条件变量上的线程唤醒
    void wakeupAll();

private:
    size_t capacity;// 任务队列的容量大小
    queue<Task *> _que;//存放数据的数据结构
    mutex _mutex;//互斥锁
    condition_variable _notEmpty;//非空条件变量
    condition_variable _notFull;//非满条件变量
    bool _flag;//标识能否退出while

};


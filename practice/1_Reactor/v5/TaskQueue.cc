#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t capa)
: _capcaity(capa)
, _que()
, _mutex()
, _notEmpty()
, _notFull()
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//添加任务与获取任务
void TaskQueue::push(ElemType &&value)
{
    unique_lock<mutex> ul(_mutex);
    while(full())
    {
        _notFull.wait(ul);
    }
    _que.push(std::move(value));
    _notEmpty.notify_one();//唤醒消费者
}

ElemType TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex);
    while(empty() && _flag)
    {
        _notEmpty.wait(ul);
    }

    if(_flag)
    {
        ElemType tmp = _que.front();
        _que.pop();
        _notFull.notify_one();//唤醒生产者

        return tmp;

    }
    else
    {
        return nullptr;
    }
}

//判断空还是满
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

bool TaskQueue::full() const
{
    return _que.size() == _capcaity;
}

//将所有等待在_notEmpty条件变量上的线程唤醒
void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notify_all();
}

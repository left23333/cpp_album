#include "eventQueue.h"

//入队
void EventQueue::inQueue(Event *pe)
{
    {
        std::lock_guard<std::mutex> guard(_mutex); //获取锁
        _queue.push(pe);
    } //自动释放锁

    _cv.notify_one(); //唤醒，通知获取队列首元素的线程醒过来
}

//出队
void EventQueue::outQueue()
{
    _queue.pop();
}

Event *EventQueue::front()
{
    while (this->isEmpty()) //队列为空线程休眠
    {
        //创建unique_lock对象，配合条件变量使用
        std::unique_lock<std::mutex> lk(_mutex);
        _cv.wait(lk); //休眠，休眠前解锁，唤醒后加锁
    }
    return _queue.front();
}

size_t EventQueue::size() const
{
    return _queue.size();
}

bool EventQueue::isEmpty() const
{
    return _queue.empty();
}

EventQueue &EventQueue::getEventQueue() //获取实例
{
    static EventQueue q; //懒汉式
    return q;
}
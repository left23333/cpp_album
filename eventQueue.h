#ifndef __EVENTQUEUE_H__
#define __EVENTQUEUE_H__

#include "event.h"
#include <mutex>
#include <queue>
#include <condition_variable>

class EventQueue
{
private:
    EventQueue() = default;                             //隐藏默认构造
    EventQueue(const EventQueue &) = delete;            //删除拷贝构造
    EventQueue &operator=(const EventQueue &) = delete; //删除拷贝赋值

    std::queue<Event *> _queue; //使用标准库队列模板

    std::mutex _mutex; //线程互斥锁
    std::condition_variable _cv;

public:
    //默认生成析构函数
    ~EventQueue() = default;
    static EventQueue &getEventQueue(); //单列模式获取队列实例

    void inQueue(Event *pe); //入队
    void outQueue();         //出队
    Event *front();          //获取队列第一个元素
    size_t size() const;     //获取队列大小
    bool isEmpty() const;    //判断是否为空
};

#endif

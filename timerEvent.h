#ifndef __TIMEREVENT_H__
#define __TIMEREVENT_H__

#include "event.h"

class TimerEvent : public Event
{
private:
    int _interval; //保存间隔时间

public:
    TimerEvent(int secs);
    ~TimerEvent() = default;
    int interval() const;                     //获取间隔时间
    void setInterval(int secs);               //设置间隔
    Event::Direct direction() const override; //获取方向
};

#endif
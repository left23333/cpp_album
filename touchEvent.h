#ifndef __TOUCHEVENT_H__
#define __TOUCHEVENT_H__

#include "event.h"

class TouchEvent : public Event
{
private:
    int _direct;

public:
    TouchEvent(int direct);
    ~TouchEvent() = default;
    Event::Direct direction() const override; //获取方向
};

#endif
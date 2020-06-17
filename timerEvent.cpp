#include "timerEvent.h"

TimerEvent::TimerEvent(int secs) : _interval(secs)
{
    this->setName("TimerEvent");
}

int TimerEvent::interval() const
{
    return _interval;
}

void TimerEvent::setInterval(int secs)
{
    _interval = secs;
}

Event::Direct TimerEvent::direction() const
{
    return Event::Direct::Right;
}
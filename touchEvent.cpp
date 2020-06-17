#include "touchEvent.h"
#include "touch_screen.h"

TouchEvent::TouchEvent(int direct) : _direct(direct)
{
    this->setName("TouchEvent");
}

Event::Direct TouchEvent::direction() const
{
    if (_direct == 1)
    {
        return Event::Direct::Left;
    }
    else if (_direct == 2)
    {
        return Event::Direct::Right;
    }
}
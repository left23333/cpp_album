#include "event.h"

std::string Event::name() const
{
    return _name;
};

void Event::setName(std::string name)
{
    _name = name;
}

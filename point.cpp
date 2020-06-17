#include "point.h"
#include <iostream>

using namespace std;

Point::Point() : _x(0), _y(0) {}

Point::Point(const int x, const int y) : _x(x), _y(y) {}

//获取x坐标
int Point::get_x() const
{
    return _x;
}

//获取y坐标
int Point::get_y() const
{
    return _y;
}

//移动坐标
void Point::move(const int x, const int y)
{
    if (x < 0 || y < 0)
    {
        cerr << "x or y must > 0" << endl;
    }
    else
    {
        _x = x;
        _y = y;
    }
}
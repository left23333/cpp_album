#include "touch_screen.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

using std::cout;
using std::endl;

Touch_screen::Touch_screen(const char *name) : _name(name), _x0(-1), _y0(-1)
{
    _fd = open(_name, O_RDWR);
    if (_fd == -1)
    {
        std::cout << "open touch error" << std::endl;
        exit(-1);
    }
}

Touch_screen::~Touch_screen()
{
    //关闭(close)
    close(_fd);
}

void Touch_screen::get_touch()
{
    while (1)
    {
        //读取输入事件(read)
        read(_fd, &_ev, sizeof(_ev)); //把从触摸屏中读取到的信息放到结构体中
        //分析结构体
        if (_ev.type == EV_ABS) //表示是一个触摸屏事件
        {
            if (_ev.code == ABS_X) //表示横坐标
            {
                if (_x0 == -1)
                {
                    _x0 = _ev.value;
                }
                _x = _ev.value;
            }
            if (_ev.code == ABS_Y)
            {
                if (_y0 == -1)
                {
                    _y0 = _ev.value;
                }
                _y = _ev.value;
            }
        }
        //当手指弹起的时候，结束循环
        //手指弹起，一直在更新点的信息
        if (_ev.type == EV_KEY && _ev.code == BTN_TOUCH && _ev.value == 0)
        {
            break;
        }
    }
    cout << __FILE__ << "," << __LINE__ << ", x0 = " << _x0 << endl;
    cout << __FILE__ << "," << __LINE__ << ", x = " << _x << endl;
}

Touch_screen::Direct Touch_screen::direct()
{
    //根据起点和终点坐标计算方向(上下左右)
    if (_x < _x0)
    {
        printf("right\n");
        _x0 = -1;
        _y0 = -1;
        return Direct::Right;
    }
    else
    {
        printf("left\n");
        _x0 = -1;
        _y0 = -1;
        return Direct::Left;
    }
}
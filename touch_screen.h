#ifndef __TOUCH_SCREEN_H__
#define __TOUCH_SCREEN_H__

#include <linux/input.h>

class Touch_screen
{
private:
    int _fd;           //触摸屏文件描述符
    const char *_name; //触摸屏文件名

    int _x0; //起点坐标
    int _y0;

    int _x; //终点坐标x
    int _y;

    struct input_event _ev; //定义输入事件的结构体变量

    enum Direct
    {
        Unknow,
        Left,
        Right
    };

public:
    Touch_screen(const char *name);
    ~Touch_screen();

    void get_touch(); //获取触摸屏位置信息
    Direct direct();  //确认移动方向
};

#endif
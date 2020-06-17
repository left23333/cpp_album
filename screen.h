#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "color.h"
#include "point.h"

class Screen
{
private:
    int _size;           //屏幕大小
    int _width;          //宽
    int _height;         //高
    int _fd;             //文件名
    int *_addr;          //映射地址
    int _bits_per_pixel; //位深
    const char *_name;   //设备名字

public:
    Screen(const char *name);
    ~Screen();

    void init_screen();                        //初始化屏幕
    void draw_point(Point point, Color color); //像素点赋颜色值
    const char *get_name() const;              //获取设备名字
    void query_attr();                         //询问属性
};

#endif
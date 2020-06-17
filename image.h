#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "screen.h"
#include <iostream>

#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <unistd.h> //close
#include <string>

class Image
{
private:
    std::string _name; //图片名
    int _fd;           //文件描述符
    int _width;        //图片宽
    int _height;       //图片高
    int _size;         //图片大小
    char *_pix_data;   //像素所需空间

    int _add_bit;      //每行填充字节数

    unsigned short _bit_per_pix; //图片色深

public:
    Image(std::string name);
    ~Image();
    void draw(Screen *screen);               //图片显示到默认位置
    void draw(Screen *screen, int x, int y); //显示到指定位置

    int width() const;        //获取宽
    int height() const;       //获取高
    int size() const;         //获取图片大小
    int abit() const;         //获取填充字节数
    std::string name() const; //获取图片名
    int bytes_per_line();     //计算一行的字节数
    int addBit();             //计算填充字节数
};

#endif
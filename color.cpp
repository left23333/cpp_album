
#include "color.h"

//默认颜色为红色
Color::Color() : _red(0xFF), _green(0x00), _blue(0x00) {}

//带参构造函数
Color::Color(char r, char g, char b) : _red(r), _green(g), _blue(b) {}

//获取颜色值
int Color::get_color() const
{
    unsigned char a = 0;
    int color;
    //char8bit置0占前8位，红绿蓝三色各占8位，4字节表示一像素点。
    color = a << 24 | _red << 16 | _green << 8 | _blue;
    return color;
}
#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{
private:
    //红绿蓝三原色
    char _red;
    char _green;
    char _blue;

public:
    Color();
    Color(char r, char g, char b);
    ~Color() = default;

    int get_color() const; //获取颜色值
};

#endif
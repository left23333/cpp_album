#ifndef __POINT_H__
#define __POINT_H__

class Point
{
private:
    //x,y表示点的坐标
    int _x;
    int _y;

public:
    Point();
    Point(const int x, const int y);
    ~Point() = default;

    int get_x() const;                   //获取x坐标
    int get_y() const;                   //获取y坐标
    void move(const int x, const int y); //移动坐标
};

#endif
#include "image.h"
#include <errno.h>
#include "point.h"

Image::Image(std::string name) : _name(name)
{
    _fd = open(name.c_str(), O_RDONLY); //打开图片
    if (_fd < 0)
    {
        throw std::runtime_error(strerror(errno));
    }

    lseek(_fd, 0x12, SEEK_SET); //移动文件头ox12
    read(_fd, &_width, 4);      //读取图片宽
    read(_fd, &_height, 4);     //读取图片高

    lseek(_fd, 0x1c, SEEK_SET);  //文件头移动到0x1c
    read(_fd, &_bit_per_pix, 2); //读取图像色深

    addBit(); //计算图片每一行的填充字节数

    //图片像素大小
    _size = (_width * _bit_per_pix / 8 + _add_bit) * _height;

    _pix_data = new char[_size]; //new图片像素大小的内存空间
    lseek(_fd, 0x36, SEEK_SET);  //移动到0x36
    read(_fd, _pix_data, _size); //读取图片颜色信息保存到_pix_data
}

Image::~Image()
{
    delete[] _pix_data; //释放空间
    close(_fd);         //关闭图片文件
}

//获取图片名
std::string Image::name() const
{
    return _name;
}

//将图片显示到屏幕上
void Image::draw(Screen *screen)
{
    Point point;
    int num = 0;

    for (int i = 0; i < height(); i++)
    {
        for (int j = 0; j < width(); j++)
        {
            Color color(*(_pix_data + num + 2), *(_pix_data + num + 1), *(_pix_data + num + 0));
            num = num + 3;
            point.move(j, height() - i - 1);
            screen->draw_point(point, color);
        }
        num = num + _add_bit; //过滤填充字节
    }
}

void Image::draw(Screen *screen, int x, int y)
{
    Point point;
    int num = 0;

    for (int i = 0; i < height(); i++)
    {
        for (int j = 0; j < width(); j++)
        {
            Color color(*(_pix_data + num + 2), *(_pix_data + num + 1), *(_pix_data + num + 0));
            num = num + 3;
            point.move(x + j, y + height() - i - 1);
            screen->draw_point(point, color);
        }
        num = num + _add_bit;
    }
}

int Image::width() const
{
    return _width;
}

int Image::height() const
{
    return _height;
}

int Image::bytes_per_line()
{
    return _width * _bit_per_pix / 8;
}

int Image::size() const
{
    return _size;
}

int Image::abit() const
{
    return _add_bit;
}

int Image::addBit()
{
    if (bytes_per_line() % 4 != 0)
    {
        _add_bit = 4 - bytes_per_line() % 4;
    }
    else
    {
        _add_bit = 0;
    }
}
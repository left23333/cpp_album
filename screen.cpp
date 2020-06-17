#include "screen.h"

#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>

#include <cstdio> //perror

#include <cstdlib> //exit

#include <unistd.h> //close

#include <sys/ioctl.h> //ioctl
#include <linux/fb.h>

#include <sys/mman.h> //mmap,munmap

Screen::Screen(const char *name)
{
    _name = name;
    _fd = open(name, O_RDWR);
    if (_fd == -1)
    {
        perror("open screen error");
        exit(1);
    }

    query_attr(); //查询屏幕参数，宽、高、位深

    _size = _width * _height * _bits_per_pixel / 8; //屏幕像素所占字节数：宽*高*位深/8

    //将屏幕映射到内存空间
    _addr = (int *)mmap(NULL, _size, PROT_READ | PROT_WRITE, MAP_SHARED, _fd, 0);
    if (_addr == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }
}

Screen::~Screen()
{
    munmap(_addr, _size); //解映射
    close(_fd);           //关闭屏幕文件
}

//初始化屏幕位白色
void Screen::init_screen()
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            *(_addr + i * 800 + j) = 0xFFFFFF;
        }
    }
}

//像素点赋颜色值
void Screen::draw_point(Point point, Color color)
{
    if ((point.get_x() >= 0 && point.get_x() < 800) && (point.get_y() >= 0 && point.get_y() < 480))
    {
        *(_addr + 800 * point.get_y() + point.get_x()) = color.get_color();
    }
}

//获取设备名字
const char *Screen::get_name() const
{
    return _name;
}

//询问属性
void Screen::query_attr()
{
    struct fb_var_screeninfo info; //定义一个结构体变量
    int ret = ioctl(_fd, FBIOGET_VSCREENINFO, &info);
    if (ret == -1)
    {
        perror("query info error");
        exit(1);
    }
    _width = info.xres; //屏宽
    //cout << "w= " << _width << endl;
    _height = info.yres; //屏高
    //cout << "h= " << _height << endl;
    _bits_per_pixel = info.bits_per_pixel; //屏幕位深
    //cout << "bpp = " << _bits_per_pixel << endl;
}


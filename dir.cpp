#include "dir.h"
#include <iostream>

#include <stdexcept> //runtime_error

#include <string.h> //strerror

#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h> //close

Dir::Dir(std::string path) : _path(path)
{
    _pdir = opendir(_path.c_str()); //c_str将string转换成字符串数组char*
    if (_pdir == NULL)
    {
        throw std::runtime_error(strerror(errno)); //抛出异常
    }
}

Dir::~Dir()
{
    closedir(_pdir); //关闭文件夹
}

//获取文件名
LinkList Dir::getFileNames()
{
    LinkList list;
    struct dirent *entry;
    while (true)
    {
        entry = readdir(_pdir); //读取文件夹
        if (entry == NULL)
        {
            break;
        }
        else if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            //跳过.和..
            continue;
        }

        //文件夹路径/文件名
        std::string pathname = _path;
        pathname += "/";
        pathname += entry->d_name;

        if (isBMP(pathname)) //判断是否为bmp图片
        {
            list.add_tail_node(pathname); //将文件路径保存到链表中
        }
    }

    return list;
}

bool Dir::isBMP(std::string path)
{
    int fd = open(path.c_str(), O_RDONLY); //打开文件
    if (fd == -1)
    {
        std::cerr << "error" << std::endl;
        return false;
    }

    char buf[2] = {0};
    read(fd, buf, 2);                    //读取文件头前两个字节
    if (buf[0] == 'B' and buf[1] == 'M') //若为BM则是bmp文件
    {
        close(fd);
        return true;
    }

    close(fd); //关闭文件
    return false;
}
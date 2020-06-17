#ifndef __DIR_H__
#define __DIR_H__

#include "dirent.h"
#include "linkList.h"
#include <string>

class Dir
{
private:
    std::string _path; //保存文件路径
    DIR *_pdir;        //保存文件夹描述符

public:
    Dir(std::string path);
    ~Dir();
    LinkList getFileNames();      //获取文件名
    bool isBMP(std::string path); //判断文件是否位bmp格式图片
};

#endif
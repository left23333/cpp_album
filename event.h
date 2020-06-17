#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

class Event
{
private:
    std::string _name;

public:
    //枚举类型定义方向
    enum class Direct
    {
        Unknow,
        Left,
        Right
    };
    Event() = default;
    virtual ~Event() = default;
    virtual Direct direction() const = 0; //纯虚函数方向
    std::string name() const;             //查看事件名

protected:
    void setName(std::string name); //设置名字
};

#endif
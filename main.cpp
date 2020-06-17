#include "screen.h"
#include "dir.h"
#include "image.h"
#include "EventQueue.h"
#include "timerEvent.h"
#include "touchEvent.h"
#include "touch_screen.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void show_production()
{
    while (true)
    {
        //创建一个定时事件对象
        Event *pe = new TimerEvent(3);
        //把事件加入队列
        EventQueue::getEventQueue().inQueue(pe);
        //等待3秒
        std::this_thread::sleep_for(chrono::seconds(3));
    }
}

void touch_production(Touch_screen &t)
{
    while (true)
    {
        t.get_touch(); //获取触摸屏位置信息

        int direct = static_cast<int>(t.direct()); //确认移动方向

        //创建一个触摸事件对象
        Event *pe = new TouchEvent(direct);
        //把事件加入队列
        EventQueue::getEventQueue().inQueue(pe);
    }
}

void consumption(Screen &screen, LinkList::Interator &it)
{
    while (true)
    {
        //获取全局唯一队列
        EventQueue &queue = EventQueue::getEventQueue();
        //提取队列中的第一个元素
        Event *pe = queue.front();
        //移除队列第一个元素
        queue.outQueue();

        cout << static_cast<int>(pe->direction()) << endl;
        if (static_cast<int>(pe->direction()) == 2)
        {
            if (it.isDone())
            {
                it.first(); //当迭代到最后一张图片，重第一张重新开始
            }
            else
            {
                it.next();
            }
            cout << __FILE__ << "," << __LINE__ << endl;
        }
        if (static_cast<int>(pe->direction()) == 1)
        {
            if (it.isFirst())
            {

                it.last(); //当迭代到最后一张图片，重第一张重新开始
            }
            else
            {
                it.prev();
            }
        }

        cout << it.currentItem() << endl; //输出当前显示图片路径
        Image image(it.currentItem());    //打开图片
        image.draw(&screen, 50, 50);      //显示图片
    }
}

int main()
{
    Screen screen("/dev/fb0");        //打开屏幕设备文件
    Dir d("./bmp");                   //打开当前文件夹下的bmp文件夹
    LinkList list = d.getFileNames(); //将bmp文件夹下的bmp图片保存到链表
    list.print_list();                //遍历并打印链表

    LinkList::Interator it = list.getIterator(); //获取迭代器

    screen.init_screen();             //初始化屏幕
    cout << it.currentItem() << endl; //输出当前显示图片路径
    Image image(it.currentItem());    //打开图片
    image.draw(&screen, 50, 50);      //显示图片

    Touch_screen t("/dev/input/event0"); //初始化触摸屏设备

    std::thread t1(show_production); //线程1生产照片
    std::thread t2(touch_production, std::ref(t));
    std::thread t3(consumption, std::ref(screen), std::ref(it)); //线程3消费图片显示到屏幕上

    t1.join(); //等待线程结束
    t2.join();
    t3.join();

    return 0;
}
#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <string>

using ElemType = std::string;

struct Node
{
    ElemType data; /* 数据域 */
    Node *next;    /* 指针域 */
    Node *prev;
};

struct List
{
    Node *first; //指向第一个数据结点
    Node *last;  //指向最后一个数据结点
    int nodeNum; //保存链表元素个数
};

class LinkList
{
private:
    List *_list;

public:
    LinkList(); //初始化双向链表
    ~LinkList();
    void add_tail_node(ElemType data); //尾插法
    void delete_tail_node();           //删除末尾结点

    int size();          //返回链表大小
    bool isEmpty();      //判断是否为空
    void print_list();   //遍历打印链表值
    const Node *first(); //获取首元素

    class Interator
    {
    private:
        const Node *_node;  //当前元素地址
        const Node *_first; //链表第一个元素地址
        const Node *_last;  //链表最后一个元素地址
        int _nodeNum;       //保存链表元素个数

    public:
        Interator(const Node *first, const Node *last, const int num);
        void first(); //当前元素设置为第一个元素
        void last();
        void next();    //下一个元素
        void prev();    //上一个元素
        bool isDone();  //是否为最后一个元素
        bool isFirst(); //判断是否为首元素

        ElemType currentItem(); //获取当前元素的地址
    };

    Interator getIterator();
};

#endif
#include <iostream>
#include "linkList.h"

using namespace std;

LinkList::LinkList()
{
    _list = new List;
    _list->first = nullptr;
    _list->last = nullptr;
    _list->nodeNum = 0;
}

LinkList::~LinkList()
{
    while (!isEmpty())
    {
        //cout << _list->nodeNum << _list->last->data << endl;
        delete_tail_node();
    }
}

void LinkList::add_tail_node(ElemType data)
{
    Node *pnew = nullptr;
    pnew = new Node;
    pnew->data = data;
    pnew->next = nullptr;
    pnew->prev = nullptr;

    if (_list->first == nullptr)
    {
        _list->first = pnew;
        _list->last = pnew;
    }
    else
    {
        //尾插法
        _list->last->next = pnew;
        pnew->prev = _list->last;
        _list->last = pnew;
    }
    _list->nodeNum++;
}

void LinkList::delete_tail_node()
{
    Node *p = _list->last;

    if (_list->nodeNum == 0)
    {
        return;
    }
    else if (_list->nodeNum == 1)
    {
        _list->first = nullptr;
        _list->last = nullptr;
    }
    else
    {
        _list->last = _list->last->prev;
        p->prev = nullptr;
        _list->last->next = nullptr;
    }
    delete p;
    _list->nodeNum--;

}

int LinkList::size()
{
    return _list->nodeNum;
}

bool LinkList::isEmpty()
{
    return _list->nodeNum == 0;
}

void LinkList::print_list()
{
    Node *p = _list->first;
    while (p)
    {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;
}

const Node *LinkList::first()
{
    return _list->first;
}

//迭代器
LinkList::Interator LinkList::getIterator()
{
    Interator it(_list->first, _list->last, _list->nodeNum);
    return it;
}

LinkList::Interator::Interator(const Node *first, const Node *last, const int num)
{
    _node = first;
    _first = first;
    _last = last;
    _nodeNum = num;
}

void LinkList::Interator::first()
{
    _node = _first;
}

void LinkList::Interator::last()
{
    _node = _last;
}

void LinkList::Interator::next()
{
    _node = _node->next;
}

void LinkList::Interator::prev()
{
    _node = _node->prev;
}

bool LinkList::Interator::isDone()
{
    return _node == _last;
}

bool LinkList::Interator::isFirst()
{
    return _node == _first;
}

ElemType LinkList::Interator::currentItem()
{
    return _node->data;
}
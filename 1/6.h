#pragma once
template <class T>
struct chainNode
{
    T element;
    chainNode<T> * next;
    chainNode() {};
    chainNode(const T& theElement)
    {
        element = theElement;
    }
    chainNode(const T& theElement, chainNode<T> * theNext)
    {
        element = theElement;
        next = theNext;
    }
};
template <class T>
class chain :public linerList<T>
{
protected:
    chainNode<T> * firstNode;//指向链表第一个元素
    int listSize;//链表长度
};
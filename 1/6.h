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
    chainNode<T> * firstNode;//ָ�������һ��Ԫ��
    int listSize;//������
};
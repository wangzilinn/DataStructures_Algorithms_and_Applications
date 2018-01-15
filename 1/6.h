#pragma once
template <class T>
struct chainNode
{
    T element;
    chainNode<T> * next;
    chainNode() {}
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
class chain:public linearList<T>
{
protected:
    chainNode<T> * firstNode;//指向链表第一个元素
    int listSize;//链表长度
    void checkList(int theIndex) const;
public:
    chain(int initCapacity = 10);//仅仅为了与数组基类统一接口
    chain(const chain<T> &);
    ~chain();

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void earse(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream & out) const;
    void binSort(int range);
};
template<class T>
chain<T>::chain(int initCapacity)//参数无实际意义，仅为了与数组线性表统一
{
    if (initCapacity < 1)
    {
        throw illegalParameterValue("大小不能小于1");
    }
    firstNode = nullptr;
    listSize = 0;
}
template<class T>
chain<T>::chain(const chain<T> & theList)
{
    listSize = theList.listSize;
    if (listSize == 0)
    {
        firstNode = nullptr;
        return;
    }
    /*
        先为第一个节点赋值，然后创建两个指针，分别指向两个链表头，然后在while中同时后移，
        在赋值时为新的链表分配空间
    */
    firstNode = new chainNode<T>(theList.firstNode->element);
    chainNode<T>* sourceNode = theList.firstNode;
    chainNode<T>* targetNode = firstNode;
    while (sourceNode != nullptr)
    {
        targetNode->next = new chainNode<T>(sourceNode->next);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = nullptr;
}
template<class T>
chain<T>::~chain()
{
    //从头开始删除
    while (firstNode != nullptr)
    {
        chainNode<T>* temp = firstNode->next;//先存下一个节点的数据
        delete firstNode;
        firstNode = temp;
    }
}
template<class T>
void chain<T>::checkList(int theIndex) const
{
    if (theIndex < 0 || theIndex   > listSize)
    {
        throw illegalParameterValue("非法的索引");
    }
}
template <class T>
T& chain<T>::get(int theIndex) const
{
    checkList(theIndex);
    chainNode<T>* pointer = firstNode;
    for (int i = 0; i < theIndex; i++)
    {
        pointer = pointer->next;
    }
    return pointer->element;
}
template <class T>
int chain<T>::indexOf(const T& theElement) const
{
    int index = 0;
    chainNode<T>* pointer = firstNode;
    while (pointer != nullptr)
    {
        if (pointer->element == theElement)
        {
            return index;
        }
        index++;
        pointer = pointer->next;
    }
    return -1;
}
template <class T>
void chain<T>::earse(int theIndex)
{
    checkList(theIndex);
    if (theIndex == 0)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    else//由于需要找到需要被删除的节点的上一个节点，所以必须把删除第一个节点的情况提取出来
    {
        int index = 0;
        chainNode<T>* pointer = firstNode;
        for (int i = 0; i < theIndex - 1; i++)//指向目标位置的上一个
        {
            pointer = pointer->next;
        }
        chainNode<T>* nextNode = pointer->next->next;
        delete pointer->next;
        pointer->next = nextNode;
        listSize--;
    }
}
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    checkList(theIndex);
    if (theIndex == 0)
    {
        chainNode<T>* nextNode = firstNode;
        firstNode = new chainNode<T>(theElement, nextNode);
    }
    else
    {
        int index = 0;
        chainNode<T>* pointer = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
        {
            pointer = pointer->next;
        }
        pointer->next = new chainNode<T>(theElement, pointer->next);
    }
    listSize++;
}
template <class T>
void chain<T>::output(ostream & out) const
{
    chainNode<T>* pointer = firstNode;
    while (pointer != nullptr)
    {
        out << pointer->element << " ";
        pointer = pointer->next;
    }
}
template <class T>
ostream & operator<<(ostream & out, chain<T> & theChain)
{
    theChain.output(out);
    return out;
}
template<class T>
void chain<T>::binSort(int range)
{
    //创建并初始化箱子
    chainNode<T> **bottom, **top;
    bottom = new chainNode<T>*[range + 1];//创建一个链表指针数组
    top = new chainNode<T>*[range + 1];
    for (int b = 0; b <= range; b++)
    {
        bottom = nullptr;
    }
    //把节点链表分配到箱子
    for (; firstNode != nullptr; firstNode = firstNode->next)
    {//把首节点firstNode加到箱子中
        int theBin = firstNode->element;//将元素类型强制转换为int
        if (bottom[theBin] == nullptr)//如果原来的箱子为空
        {//移动箱子顶部指针和底部指针都指向第一个节点
            bottom[theBin] = top[theBin] = firstNode;
        }
        else
        {
            //箱子不空
            top[theBin]->next = firstNode;//链表尾部，其实next指向哪无所谓
            top[theBin] = firstNode;
        }
    }
    //把箱子中的节点收集到有序列表
    chainNode<T> *y = nullptr;
    for (int theBin = 0; theBin <= range; theBin++)
    {
        if (bottom[theBin] != nullptr)
        {
            //箱子不空
            if (y == nullptr)
            {
                firstNode = bottom[theBin];
            }
            else
            {
                y->next = bottom[theBin];
            }
            y = top[theBin];
        }
    }
    if (y != nullptr)
    {
        y->next = nullptr;
    }
    delete[] bottom;
    delete[] top;
}
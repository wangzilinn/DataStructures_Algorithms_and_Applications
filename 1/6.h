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
class chain :public linearList<T>
{
protected:
    chainNode<T> * firstNode;//ָ�������һ��Ԫ��
    int listSize;//������
    void checkList(int theIndex) const;
public:
    chain(int initCapacity = 10);//����Ϊ�����������ͳһ�ӿ�
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
    void binSort(unsigned int from, unsigned int to);
};
template<class T>
chain<T>::chain(int initCapacity)//������ʵ�����壬��Ϊ�����������Ա�ͳһ
{
    if (initCapacity < 1)
    {
        throw illegalParameterValue("��С����С��1");
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
        ��Ϊ��һ���ڵ㸳ֵ��Ȼ�󴴽�����ָ�룬�ֱ�ָ����������ͷ��Ȼ����while��ͬʱ���ƣ�
        �ڸ�ֵʱΪ�µ��������ռ�
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
    //��ͷ��ʼɾ��
    while (firstNode != nullptr)
    {
        chainNode<T>* temp = firstNode->next;//�ȴ���һ���ڵ������
        delete firstNode;
        firstNode = temp;
    }
}
template<class T>
void chain<T>::checkList(int theIndex) const
{
    if (theIndex < 0 || theIndex   > listSize)
    {
        throw illegalParameterValue("�Ƿ�������");
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
    else//������Ҫ�ҵ���Ҫ��ɾ���Ľڵ����һ���ڵ㣬���Ա����ɾ����һ���ڵ�������ȡ����
    {
        int index = 0;
        chainNode<T>* pointer = firstNode;
        for (int i = 0; i < theIndex - 1; i++)//ָ��Ŀ��λ�õ���һ��
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
    //��������ʼ������
    chainNode<T> **bottom, **top;
    bottom = new chainNode<T>*[range + 1];//����һ������ָ������
    top = new chainNode<T>*[range + 1];
    for (int b = 0; b <= range; b++)
    {
        bottom[b] = nullptr;
    }
    //�ѽڵ�������䵽����
    for (; firstNode != nullptr; firstNode = firstNode->next)
    {//���׽ڵ�firstNode�ӵ�������
        int theBin = firstNode->element;//��Ԫ������ǿ��ת��Ϊint
        if (bottom[theBin] == nullptr)//���ԭ��������Ϊ��
        {//�ƶ����Ӷ���ָ��͵ײ�ָ�붼ָ���һ���ڵ�
            bottom[theBin] = top[theBin] = firstNode;
        }
        else
        {
            //���Ӳ���
            top[theBin]->next = firstNode;
            top[theBin] = firstNode;//top�����ƶ���һ��
        }
    }
    //�������еĽڵ��ռ��������б�
    chainNode<T> *y = nullptr;
    for (int theBin = 0; theBin <= range; theBin++)
    {
        if (bottom[theBin] != nullptr)
        {
            //���Ӳ���
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
template <class T>
void chain<T>::binSort(unsigned int from, unsigned int to)
{
    if (to < from)
        throw illegalParameterValue("to������ڵ���from");
    int theNumberOfBins = to - from + 1;//ȷ�����Ӹ���
    chainNode<T>** top = new chainNode<T>*[theNumberOfBins];//����ָ�����Ӷ���������β����ָ������
    chainNode<T>** bottom = new chainNode<T>*[theNumberOfBins];

    for (int i = 0; i < theNumberOfBins; i++)
    {
        bottom[i] = top[i] = nullptr;//��ָֹ����ָ
    }
    //װ������
    while (firstNode != nullptr)
    {
        int binNumber = firstNode->element - from;
        if (bottom[binNumber] == nullptr)//�������Ϊ�գ���ô�����Ӷ�Ӧ��top��bottom��ָ�����ӵײ���ͬʱָ������ͷ
        {
            bottom[binNumber] = top[binNumber] = firstNode;
        }
        else
        {
            //������������⣺
            //ԭ����topָ������һ��λ�ã�
            //��һ����ʹtop����һ��ָ������ͷ���������������ӵ���һ���ڵ�ָ������ͷ��
            //�ڶ�����ʹtopָ������ͷ������top�����ƶ���һ��
            top[binNumber]->next = firstNode;
            top[binNumber] = firstNode;
        }
        firstNode = firstNode->next;
    }
    //��������ȡ��
    chainNode<T> * pointer = nullptr;//�������Ӹ������ӵ�ָ��
    for (int i = 0; i < theNumberOfBins; i++)
    {
        if (bottom[i] != nullptr)
        {
            if (pointer == nullptr)//Ѱ�ҵ�һ���ǿյ�����
            {
                firstNode = bottom[i];
            }
            else
            {
                pointer->next = bottom[i];//��ʱpointerָ�������һ�����ӵ�ͷ��������������һ��ָ�򱾴�ѭ���ĵ�
            }
            pointer = top[i];
        }
    }
    pointer->next = nullptr;
    delete[] bottom;
    delete[] top;
}
void testAt6();
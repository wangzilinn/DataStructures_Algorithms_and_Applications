#pragma once
//所有函数随便测试了一下没啥问题
template <class T>
void changeLength1D(T* &head, int oldLength, int newLength)
{
    T* temp = new T[newLength];
    copy(head, head + min(oldLength, newLength) , temp);
    delete[] head;
    head = temp;
}
//5-3 改变二维数组长度
template <class T>
void changeLength2D(T ** &head, int row, int oldLength, int newLength)//未测试
{
    T* temp = new T[newLength];
    copy(head[row], head[row] + min(oldLength, newLength), temp);//将旧的该维数组复制到新的空间
    delete[]head[row];
    head[row] = temp;
}

//class arrayList
template<class T>
class linerList//线性表,抽象类
{
public:
    virtual ~linerList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;  
    virtual T& get() const = 0;
    virtual int indexOf() const = 0;
    virtual void earse(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(ostream& out) const = 0;
};
template <class T>
class arrayList:public linerList<T>
{
protected: 
    T* element;
    int arrayLength;//数组开辟空间长度
    int listSize;//线性表长度
    void checkList(int theIndex) const;
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>& element);//记住是const引用
    ~arrayList() { delete[] element; };
    //ADT method
    bool empty() const { return (listSize == 0) ? true : false; };
    int size() const { return listSize; };
    T& get(int theIndex) const;//参数为索引的都要进行索引有效性检查，其函数体较长，所以不适合直接写在声明中
    int indexOf(const T& theElement) const;
    void earse(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;
    int capacity() const { return arrayLength; };
    void trimToSize();
    void removeRange(int start, int end);
    T& operator[](int i)const;
    bool operator!=(const arrayList<T>& theElemrnt) const;
    bool operator==(const arrayList<T>& theElement) const;

};
//构造函数
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        throw illegalParameterValue("不能小于1");
    }
    element = new T[initialCapacity];
    arrayLength = initialCapacity;
    listSize = 0;
}
//复制构造函数
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    for (int i = 0; i < arrayLength; i++)
    {
        element[i] = theList.element[i];
    }
}
template <class T>
void arrayList<T>::checkList(int theIndex) const
{
    if (theIndex < 0 || theIndex > arrayLength - 1)
    {
        throw illegalParameterValue("非法的索引");
    }
}
template<class T>
T & arrayList<T>::get(int theIndex) const
{
    checkList(theIndex);
    return element[theIndex];
}
template <class T>
int arrayList<T>::indexOf(const T& theElement) const
{
    int theIndex = (int)(find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
    {
        return -1;//未找到
    }
    else
    {
        return theIndex;
    }
}
template <class T>
void arrayList<T>::earse(int theIndex)
{
    checkList(theIndex);
    if (arrayLength / 4 > listSize)
    {
        changeLength1D(element, arrayLength, arrayLength / 2);//防止数组过长
    }
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    listSize--;
    //element[listSize].~T();//???啥意思
}
template <class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
    checkList(theIndex);
    if (arrayLength == listSize)
    {
        changeLength1D(element, listSize, arrayLength * 2);
    }
    copy(element + theIndex, element + listSize, element + theIndex + 1);
    listSize++;
    element[theIndex] = theElement;
}
template <class T>
void arrayList<T>::output(ostream& out) const//用<<运算符重载函数调用output就不需要使<<作为友元了
{
    copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}
//运算符重载
template <class T>
ostream& operator<<(ostream& out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}
//5-5 改变数组开辟空间长度到正好为线性表长度（特例：如果数组长度为0，则开辟空间长度为1）
template <class T>
void arrayList<T>::trimToSize()
{
    if (arrayLength == listSize)
        return;//如果长度正好相等，则满足条件直接退出
    if (listSize == 0)//实现特例情况：如果线性表为空，则开辟空间为1
    {
        delete[] element;
        element = new T[1];
        arrayLength = 1;//记得要更新成员值
        return;//错：忘记了返回
    }
    //实现其他情况：
    /*在下面的两个函数调用都能够实现函数功能，因为changeLength1D
    仅仅是开辟了一个空间，把旧的数组内容复制到了新的空间中去，复制
    的长度为 min(第二个参数，第三个参数)，在本题情况下，第二个参
    数取原数组开辟空间长度还是原线性表长度其实是无关紧要的。   
    */
    //changeLength1D(element, arrayLength, listSize);//第二个参数为原线性表长度，第三个参数为为新的线性表长度
    changeLength1D(element, listSize, listSize);//第二个参数为原线性表长度，第三个参数为为新的线性表长度
    arrayLength = listSize;
}
template <class T>
void arrayList<T>::removeRange(int start, int end)
{
    if (start <= end)
    {
        checkList(start);
        checkList(end);
        int removeLength = end - start + 1;//删除的元素的个数
        listSize = listSize - removeLength;//新的线性表长度
        for (int i = start; i < listSize; i++)
        {
            element[i] = element[i + removeLength];
        }
        
    }
}
//5-7 重载操作符[]
template <class T>//返回一个左值，可以位于等号左边或右边
T& arrayList<T>::operator[](int i) const
{
    checkList(i);
    return element[i];
}
//5-9 重载操作符！=
template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& theElement) const
{
    if (listSize != theElement.listSize)
        return true;
    for (int i = 0; i < listSize; i++)
    {
        if (element[i] != theElement.element[i])
            return true;
    }
    return false;
}
template<class T>
bool arrayList<T>::operator==(const arrayList<T>& theElement) const
{
    if (listSize != theElement.listSize)
        return false;
    for (int i = 0; i < listSize; i++)
    {
        if (element[i] != theElement.element[i])
            return false;
    }
    return true;
}
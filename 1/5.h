#pragma once
//���к�����������һ��ûɶ����
template <class T>
void changeLength1D(T* &head, int oldLength, int newLength)
{
    T* temp = new T[newLength];
    copy(head, head + min(oldLength, newLength) , temp);
    delete[] head;
    head = temp;
}
//5-3 �ı��ά���鳤��
template <class T>
void changeLength2D(T ** &head, int row, int oldLength, int newLength)//δ����
{
    T* temp = new T[newLength];
    copy(head[row], head[row] + min(oldLength, newLength), temp);//���ɵĸ�ά���鸴�Ƶ��µĿռ�
    delete[]head[row];
    head[row] = temp;
}

//class arrayList
template<class T>
class linerList//���Ա�,������
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
    int arrayLength;//���鿪�ٿռ䳤��
    int listSize;//���Ա���
    void checkList(int theIndex) const;
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>& element);//��ס��const����
    ~arrayList() { delete[] element; };
    //ADT method
    bool empty() const { return (listSize == 0) ? true : false; };
    int size() const { return listSize; };
    T& get(int theIndex) const;//����Ϊ�����Ķ�Ҫ����������Ч�Լ�飬�亯����ϳ������Բ��ʺ�ֱ��д��������
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
//���캯��
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        throw illegalParameterValue("����С��1");
    }
    element = new T[initialCapacity];
    arrayLength = initialCapacity;
    listSize = 0;
}
//���ƹ��캯��
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
        throw illegalParameterValue("�Ƿ�������");
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
        return -1;//δ�ҵ�
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
        changeLength1D(element, arrayLength, arrayLength / 2);//��ֹ�������
    }
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    listSize--;
    //element[listSize].~T();//???ɶ��˼
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
void arrayList<T>::output(ostream& out) const//��<<��������غ�������output�Ͳ���Ҫʹ<<��Ϊ��Ԫ��
{
    copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}
//���������
template <class T>
ostream& operator<<(ostream& out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}
//5-5 �ı����鿪�ٿռ䳤�ȵ�����Ϊ���Ա��ȣ�������������鳤��Ϊ0���򿪱ٿռ䳤��Ϊ1��
template <class T>
void arrayList<T>::trimToSize()
{
    if (arrayLength == listSize)
        return;//�������������ȣ�����������ֱ���˳�
    if (listSize == 0)//ʵ�����������������Ա�Ϊ�գ��򿪱ٿռ�Ϊ1
    {
        delete[] element;
        element = new T[1];
        arrayLength = 1;//�ǵ�Ҫ���³�Աֵ
        return;//�������˷���
    }
    //ʵ�����������
    /*������������������ö��ܹ�ʵ�ֺ������ܣ���ΪchangeLength1D
    �����ǿ�����һ���ռ䣬�Ѿɵ��������ݸ��Ƶ����µĿռ���ȥ������
    �ĳ���Ϊ min(�ڶ�������������������)���ڱ�������£��ڶ�����
    ��ȡԭ���鿪�ٿռ䳤�Ȼ���ԭ���Ա�����ʵ���޹ؽ�Ҫ�ġ�   
    */
    //changeLength1D(element, arrayLength, listSize);//�ڶ�������Ϊԭ���Ա��ȣ�����������ΪΪ�µ����Ա���
    changeLength1D(element, listSize, listSize);//�ڶ�������Ϊԭ���Ա��ȣ�����������ΪΪ�µ����Ա���
    arrayLength = listSize;
}
template <class T>
void arrayList<T>::removeRange(int start, int end)
{
    if (start <= end)
    {
        checkList(start);
        checkList(end);
        int removeLength = end - start + 1;//ɾ����Ԫ�صĸ���
        listSize = listSize - removeLength;//�µ����Ա���
        for (int i = start; i < listSize; i++)
        {
            element[i] = element[i + removeLength];
        }
        
    }
}
//5-7 ���ز�����[]
template <class T>//����һ����ֵ������λ�ڵȺ���߻��ұ�
T& arrayList<T>::operator[](int i) const
{
    checkList(i);
    return element[i];
}
//5-9 ���ز�������=
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
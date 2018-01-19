#pragma once
template <class T>
class CircularArrayQuene
{
private:
    T * quene;
    int queneFront;//指向头元素的上一个元素
    int queneBack;//指向尾元素
    int queneLength;
    int arrayLength;
public:
    CircularArrayQuene(int initialCapacity = 10);
    ~CircularArrayQuene();
    bool empty() const { return queneLength == 0; }
    int size() const { return queneLength; }
    T& front() const;//返回头元素
    T& back() const; //返回尾元素
    void push(const T& theElement);
    T& pop();//删除尾元素并返回尾元素
};
template <class T>
CircularArrayQuene<T>::CircularArrayQuene(int initialCapacity)
{
    if (initialCapacity < 10)
    {
        initialCapacity = 10;
    }
    arrayLength = initialCapacity;
    quene = new T[arrayLength]();
    queneFront = queneBack = arrayLength - 1;
    queneLength = 0;
}
template <class T>
CircularArrayQuene<T>::~CircularArrayQuene()
{
    delete[] quene;
}
template <class T>
T& CircularArrayQuene<T>::front() const
{
    if (queneLength > 0)
    {
        return quene[(queneFront + 1) / arrayLength];
    }
    throw "队列为空";
}
template <class T>
T& CircularArrayQuene<T>::back() const
{
    if (queneLength > 0)
    {
        return quene[queneBack];
    }
    throw "队列为空";
}
template <class T>
void CircularArrayQuene<T>::push(const T& theElement)
{
    if (queneLength == (arrayLength - 1))
    {
        T* temp = new T[2 * arrayLength];
        copy(quene, quene + arrayLength, temp);
        int newArrayLength = 2 * arrayLength;
        for (int i = arrayLength - 1, j = 1; i > queneFront; i--, j++)
        {
            temp[newArrayLength - j] = quene[i];//从后往前复制（注意：queneFront指向的是队列头前一个元素）
        }
        int numberTobeMoved = arrayLength - queneFront;//头指针随着空间增长向右移动的长度
        queneFront = newArrayLength - numberTobeMoved;//更新头指针位置
        arrayLength = newArrayLength;
        delete[] quene;
        quene = temp;
        //以上数组长度更新完毕
    }
    queneBack = (queneBack + 1) % arrayLength;
    quene[queneBack] = theElement;
    queneLength++;
}
template <class T>
T& CircularArrayQuene<T>::pop()
{
    queneFront = (queneFront + 1) % arrayLength;//将头指针移到下一个元素
    queneLength--;
    return quene[queneFront];
}
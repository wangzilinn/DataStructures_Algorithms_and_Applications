#pragma once
template <class T>
class CircularArrayQuene
{
private:
    T * quene;
    int queneFront;//ָ��ͷԪ�ص���һ��Ԫ��
    int queneBack;//ָ��βԪ��
    int queneLength;
    int arrayLength;
public:
    CircularArrayQuene(int initialCapacity = 10);
    ~CircularArrayQuene();
    bool empty() const { return queneLength == 0; }
    int size() const { return queneLength; }
    T& front() const;//����ͷԪ��
    T& back() const; //����βԪ��
    void push(const T& theElement);
    T& pop();//ɾ��βԪ�ز�����βԪ��
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
    throw "����Ϊ��";
}
template <class T>
T& CircularArrayQuene<T>::back() const
{
    if (queneLength > 0)
    {
        return quene[queneBack];
    }
    throw "����Ϊ��";
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
            temp[newArrayLength - j] = quene[i];//�Ӻ���ǰ���ƣ�ע�⣺queneFrontָ����Ƕ���ͷǰһ��Ԫ�أ�
        }
        int numberTobeMoved = arrayLength - queneFront;//ͷָ�����ſռ����������ƶ��ĳ���
        queneFront = newArrayLength - numberTobeMoved;//����ͷָ��λ��
        arrayLength = newArrayLength;
        delete[] quene;
        quene = temp;
        //�������鳤�ȸ������
    }
    queneBack = (queneBack + 1) % arrayLength;
    quene[queneBack] = theElement;
    queneLength++;
}
template <class T>
T& CircularArrayQuene<T>::pop()
{
    queneFront = (queneFront + 1) % arrayLength;//��ͷָ���Ƶ���һ��Ԫ��
    queneLength--;
    return quene[queneFront];
}
#pragma once
template<class T>
class stack
{
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() = 0;//����ջ��Ԫ������
    virtual void pop() = 0;//ɾ��ջ��Ԫ��
    virtual void push(const T& theElements) = 0;
};
template<class T>
class linkedStack :public stack<T>
{
    //ʵ��һ������ջ��������ͷ����
private:
    chainNode<T>* stackTop;
    int stackSize;
public:
    linkedStack() { stackTop = nullptr; stackSize = 0; }
    ~linkedStack();
    bool empty() const { return stackSize == 0; }
    int size() const { return stackSize; }
    T& top();
    void pop();
    void push(const T& theElement);
    bool has(const T& theElement) const;
};
template <class T>
linkedStack<T>::~linkedStack()
{
    while (stackTop != nullptr)
    {
        chainNode<T>* temp = stackTop->next;
        delete stackTop;
        stackTop = temp;
    }
}
template <class T>
T& linkedStack<T>::top()
{
    if (stackSize == 0)
    {
        throw illegalParameterValue("ջΪ��");
    }
    return stackTop->element;
}
template <class T>
void linkedStack<T>::pop()
{
    chainNode<T>* temp = stackTop->next;
    delete stackTop;
    stackTop = temp;
    stackSize--;
}
template <class T>
void linkedStack<T>::push(const T& theElement)
{
    chainNode<T>* newNode = new chainNode<T>;
    newNode->element = theElement;
    newNode->next = stackTop;
    stackTop = newNode;
    stackSize++;
}
template <class T>
bool linkedStack<T>::has(const T& theElement) const
{
    chainNode<T>* pointer = stackTop;
    while (pointer != nullptr)
    {
        if (pointer->element == theElement)
            return true;
        pointer = pointer->next;
    }
    return false;
}
//ƥ������
void printMatchedPairs(string expr);
//��ŵ��
void towerOfHanoi(int n, int from, int to, int auxiliary);
void towerOfHanoi(int n);
static void moveAndShow(int n, int from, int to, int auxiliary);//ֻ�Ǹ�����ĺ�ŵ����������
//�г�����
class CarSort
{
private:
    linkedStack<int> *track;
    int *inputOrder;
    int numberOfCars;
    int numberOfTracks;//��������Ŀ
    int smallestCarTrack;//ͣ������С��ų���Ļ�����
    int nextCarToOutput;//��һ��Ҫ���Ƴ��ĳ���
public:
    CarSort(int theInputOrder[], const int theNumberOfCars, const int theNumberOfTracks);
    ~CarSort();
    bool startSort();
};
//���ߵȼ���
class OfflineEquirlenceClass
{
private:
    int n;//Ԫ����Ŀ
    int numberOfRelationships;//��ϵ��Ŀ
    linkedStack<int>* stack;
    linkedStack<int>* numberList;
    bool *alreadyOut;
public:
    OfflineEquirlenceClass(const int n, const int theNumberOfRelationships, int** theRelationshipList);
    ~OfflineEquirlenceClass();
    void solve();
};
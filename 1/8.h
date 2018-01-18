#pragma once
template<class T>
class stack
{
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() = 0;//返回栈顶元素引用
    virtual void pop() = 0;//删除栈顶元素
    virtual void push(const T& theElements) = 0;
};
template<class T>
class linkedStack :public stack<T>
{
    //实现一个链表栈，在链表头插入
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
        throw illegalParameterValue("栈为空");
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
//匹配括号
void printMatchedPairs(string expr);
//汉诺塔
void towerOfHanoi(int n, int from, int to, int auxiliary);
void towerOfHanoi(int n);
static void moveAndShow(int n, int from, int to, int auxiliary);//只是给上面的汉诺塔函数调用
//列车重排
class CarSort
{
private:
    linkedStack<int> *track;
    int *inputOrder;
    int numberOfCars;
    int numberOfTracks;//缓冲轨道数目
    int smallestCarTrack;//停靠着最小编号车厢的缓冲轨道
    int nextCarToOutput;//下一个要被移出的车辆
public:
    CarSort(int theInputOrder[], const int theNumberOfCars, const int theNumberOfTracks);
    bool startSort();
};
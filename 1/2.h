#pragma once
//9
template<class T>
void c2_9Rank(T a[], int n, int r[])
{
    for (int i = 0; i < n; i++)
    {
        r[i] = 0;
    }//清空排序列表
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i] > a[j])
                r[i]++;
        }
    }
}
//11 bubbleSort
template <class T>
void c2_11BubbleSort(T a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (n - i - 1); j++)//注意这里的减一操作，每次冒泡，比较的次数是数组长度减一
        {
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        }
    }
}
//13 c2_13
template <class T>
T* c2_13Insert(T originalArray[], int originalLength, T insertNumber)
{
    T* newArray = new T[originalLength + 1];
    for (int i = 0; i < originalLength; i++)
    {
        newArray[i] = originalArray[i];
    }//为新的数组赋值
    int i;
    for (i = originalLength - 1; i > 0 && insertNumber < newArray[i]; i--)//数组最后一个下表是数组长度减一
    {
        newArray[i + 1] = newArray[i];//向右移动一位
    }
    newArray[i + 1] = insertNumber;
    return newArray;
}
//15 选择排序
template <class T>
void c2_15SelectionSort(T a[], int arrayLength)
{
    bool sorted = false;
    for (int i = arrayLength - 1; i > 0; i--)//i代表的是数组下标，不是代表本次循环的数组长度了
    {
        int indexOfMax = 0;
        sorted = true;
        for (int j = 1; j < i + 1; j++)
            /*i + 1可以这样想：
            只想第一次比较，第一次比较要比较全部 - 1次
            （因为不用跟自己比较，所以减1）
            ，所以结束的判断条件是 < 数组长度
            （注意此时i的值已经不是数组长度了,而是数组长度减1)
            所以结束条件是 < i + 1*/
        {
            if (a[j] > a[indexOfMax])
            {
                indexOfMax = j;
            }
            else
            {
                sorted = false;//如果已经排序好了，那么每次都会进上面的if。
            }
        }
        swap(a[indexOfMax], a[i]);
    }
}
//17 插入排序
template <class T>
void c2_17InsertSort(T a[], int arrayLength)
{
    for (int i = 1; i < arrayLength; i++)
    {
        T temp = a[i];
        int j = 0;
        for (j = i - 1; j >= 0 && temp < a[j]; j--)
        {
            a[j + 1] = a[j];
        }
        a[j + 1] = temp;
    }
}
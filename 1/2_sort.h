#pragma once
//9
template<class T>
void c2_9Rank(T a[], int n, int r[])
{
    for (int i = 0; i < n; i++)
    {
        r[i] = 0;
    }//��������б�
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
        for (int j = 0; j < (n - i - 1); j++)//ע������ļ�һ������ÿ��ð�ݣ��ȽϵĴ��������鳤�ȼ�һ
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
    }//Ϊ�µ����鸳ֵ
    int i;
    for (i = originalLength - 1; i > 0 && insertNumber < newArray[i]; i--)//�������һ���±������鳤�ȼ�һ
    {
        newArray[i + 1] = newArray[i];//�����ƶ�һλ
    }
    newArray[i + 1] = insertNumber;
    return newArray;
}
//15 ѡ������
template <class T>
void c2_15SelectionSort(T a[], int arrayLength)
{
    bool sorted = false;
    for (int i = arrayLength - 1; i > 0; i--)//i������������±꣬���Ǵ�����ѭ�������鳤����
    {
        int indexOfMax = 0;
        sorted = true;
        for (int j = 1; j < i + 1; j++)
            /*i + 1���������룺
            ֻ���һ�αȽϣ���һ�αȽ�Ҫ�Ƚ�ȫ�� - 1��
            ����Ϊ���ø��Լ��Ƚϣ����Լ�1��
            �����Խ������ж������� < ���鳤��
            ��ע���ʱi��ֵ�Ѿ��������鳤����,�������鳤�ȼ�1)
            ���Խ��������� < i + 1*/
        {
            if (a[j] > a[indexOfMax])
            {
                indexOfMax = j;
            }
            else
            {
                sorted = false;//����Ѿ�������ˣ���ôÿ�ζ���������if��
            }
        }
        swap(a[indexOfMax], a[i]);
    }
}
//17 ��������
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
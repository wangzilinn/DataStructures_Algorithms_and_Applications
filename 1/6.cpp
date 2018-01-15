#include "stdafx.h"
//数组实现并查集
int *equivClass,//等价数组类
    n;//元素个数
void initialize(int numberOfElements)
{
    //用每个类的一个元素，初始化numberOfElements个类
    n = numberOfElements;
    equivClass = new int[n + 1];
    for (int e = 1; e <= n; e++)
    {
        equivClass[e] = e;
    }
}

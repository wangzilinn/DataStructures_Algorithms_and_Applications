#include "stdafx.h"
//����ʵ�ֲ��鼯
int *equivClass,//�ȼ�������
    n;//Ԫ�ظ���
void initialize(int numberOfElements)
{
    //��ÿ�����һ��Ԫ�أ���ʼ��numberOfElements����
    n = numberOfElements;
    equivClass = new int[n + 1];
    for (int e = 1; e <= n; e++)
    {
        equivClass[e] = e;
    }
}

#include"stdafx.h"
//ƥ������
void printMatchedPairs(string expr)
{
    linkedStack<int> a;
    int length = static_cast<int>(expr.size());
    for (int i = 0; i < length; i++)
    {
        if (expr.at(i) == '(')
        {
            a.push(i);
        }
        else if (expr.at(i) == ')')
        {
            try
            {
                cout << a.top() << " " << i << endl;
                a.pop();//û��ջƥ��
            }
            catch (...)
            {
                cout << "ջΪ��" << endl;
            }
        }
    }
    while (!a.empty())
    {
        cout << "û��ƥ�������" << endl;
        a.pop();
    }
}
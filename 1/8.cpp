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
//��ŵ�� �ݹ�
void towerOfHanoi(int n, int from, int to, int auxiliary)
{
    if (n > 0)
    {
        towerOfHanoi(n - 1, from, auxiliary, to);
        cout << "move " << from << " to " << to << endl;
        towerOfHanoi(n - 1, auxiliary, to, from);
    }
}
//��ŵ�� ջ
linkedStack<int> tower[4];
void towerOfHanoi(int n)
{
    for (int d = n; d > 0; d--)
    {
        tower[1].push(d);
    }
}
void moveAndShow(int n, int from, int to, int auxiliary)
{
    moveAndShow(n - 1, from, auxiliary, to);
    int d = tower[from].top();//�����Ƕ��������ĵ���չ��û��ʲôѧϰ��ֵ
    tower[from].pop();
    tower[to].push(d);
    moveAndShow(n - 1, auxiliary, to, from);
}
//�г����ţ�
linkedStack<int> *track;
int numberOfCars;
int numberOfTracks;//��������Ŀ
int smallestCar;//�ڻ������б����С�ĳ���
int itsTrack;//ͣ������С��ų���Ļ�����
bool railRoad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
{
    track = new linkedStack<int>[theNumberOfTracks];
    for (int i = 0; i < theNumberOfCars; i++)
    {

    }
}

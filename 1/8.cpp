#include"stdafx.h"
//匹配括号
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
                a.pop();//没有栈匹配
            }
            catch (...)
            {
                cout << "栈为空" << endl;
            }
        }
    }
    while (!a.empty())
    {
        cout << "没有匹配的括号" << endl;
        a.pop();
    }
}
//汉诺塔 递归
void towerOfHanoi(int n, int from, int to, int auxiliary)
{
    if (n > 0)
    {
        towerOfHanoi(n - 1, from, auxiliary, to);
        cout << "move " << from << " to " << to << endl;
        towerOfHanoi(n - 1, auxiliary, to, from);
    }
}
//汉诺塔 栈
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
    int d = tower[from].top();//仅仅是对上面程序的的拓展，没有什么学习价值
    tower[from].pop();
    tower[to].push(d);
    moveAndShow(n - 1, auxiliary, to, from);
}
//列车重排：
linkedStack<int> *track;
int numberOfCars;
int numberOfTracks;//缓冲轨道数目
int smallestCar;//在缓冲区中编号最小的车厢
int itsTrack;//停靠着最小编号车厢的缓冲轨道
bool railRoad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
{
    track = new linkedStack<int>[theNumberOfTracks];
    for (int i = 0; i < theNumberOfCars; i++)
    {

    }
}

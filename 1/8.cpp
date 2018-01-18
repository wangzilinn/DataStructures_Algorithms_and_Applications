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
CarSort::CarSort(int theInputOrder[], const int theNumberOfCars, const int theNumberOfTracks)
{
    numberOfCars = theNumberOfCars;
    numberOfTracks = theNumberOfTracks;//缓冲轨道数目
    track = new linkedStack<int>[theNumberOfTracks];
    inputOrder = theInputOrder;
    nextCarToOutput = 1;
    smallestCarTrack = -1;
}
bool CarSort::startSort()
{
    for (int i = 0; i < numberOfCars; i++)
    {
        if (inputOrder[i] == nextCarToOutput)
        {
            cout << "直接移动" << inputOrder[i] << "号车厢到出轨道" << endl;
            nextCarToOutput++;
            //从缓冲区中找有没有可以直接移出的车厢：
            bool hasNextLoop = true;
            while (hasNextLoop)
            {
                hasNextLoop = false;
                for (int j = 0; j < numberOfTracks; j++)
                {
                    if ((!track[j].empty()) && (track[j].top() == nextCarToOutput))
                    {
                        cout << "移动缓冲区" << j << "中的" << track[j].top() << "号车厢到出轨道" << endl;
                        track[j].pop();
                        nextCarToOutput++;
                        hasNextLoop = true;//如果本次遍历发现有能进入出轨道的，则再次进行遍历
                    }
                }
            }

        }
        else
        {
            int minDeviation = numberOfCars;
            smallestCarTrack = -1;
            //寻找满足条件的最佳缓冲区
            for (int j = 0; j < numberOfTracks; j++)
            {
                if((!track[j].empty()) && (inputOrder[i] < track[j].top()))
                {
                    int deviation = track[j].top() - inputOrder[i];
                    if (deviation <= minDeviation)
                    {
                        minDeviation = deviation;
                        smallestCarTrack = j;
                    }
                }
            }
            if (smallestCarTrack == -1)//如果非空的栈没有合适的位置，就看看有没有空栈可以放
            {
                for (int j = 0; j < numberOfTracks; j++)
                {
                    if (track[j].empty())
                    {
                        smallestCarTrack = j;
                        break;
                    }
                }               
            }
            if (smallestCarTrack == -1)
            {
                cout << "无法放入缓冲区" << endl;
            }
            //将车厢放入找到的缓冲区：
            track[smallestCarTrack].push(inputOrder[i]);
            cout << "把" << inputOrder[i] << "号车厢放入" << smallestCarTrack << "号缓冲区" << endl;
        }
    }
    return true;
}

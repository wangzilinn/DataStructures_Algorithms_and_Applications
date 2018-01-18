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
CarSort::CarSort(int theInputOrder[], const int theNumberOfCars, const int theNumberOfTracks)
{
    numberOfCars = theNumberOfCars;
    numberOfTracks = theNumberOfTracks;//��������Ŀ
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
            cout << "ֱ���ƶ�" << inputOrder[i] << "�ų��ᵽ�����" << endl;
            nextCarToOutput++;
            //�ӻ�����������û�п���ֱ���Ƴ��ĳ��᣺
            bool hasNextLoop = true;
            while (hasNextLoop)
            {
                hasNextLoop = false;
                for (int j = 0; j < numberOfTracks; j++)
                {
                    if ((!track[j].empty()) && (track[j].top() == nextCarToOutput))
                    {
                        cout << "�ƶ�������" << j << "�е�" << track[j].top() << "�ų��ᵽ�����" << endl;
                        track[j].pop();
                        nextCarToOutput++;
                        hasNextLoop = true;//������α����������ܽ��������ģ����ٴν��б���
                    }
                }
            }

        }
        else
        {
            int minDeviation = numberOfCars;
            smallestCarTrack = -1;
            //Ѱ��������������ѻ�����
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
            if (smallestCarTrack == -1)//����ǿյ�ջû�к��ʵ�λ�ã��Ϳ�����û�п�ջ���Է�
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
                cout << "�޷����뻺����" << endl;
            }
            //����������ҵ��Ļ�������
            track[smallestCarTrack].push(inputOrder[i]);
            cout << "��" << inputOrder[i] << "�ų������" << smallestCarTrack << "�Ż�����" << endl;
        }
    }
    return true;
}

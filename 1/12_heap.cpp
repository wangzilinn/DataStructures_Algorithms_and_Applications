#include "stdafx.h"
//���������Ķ�������
static void display(int * t)
{
	cout << *t << " ";
}

void testAt12()
{
	int n = 5;
	int* root = new int[2 * n]
	{ 0,20,15,2,14,10 };//Ĭ�ϳ�ʼ��
	maxHeap<int> testHeap(root, n);
	//testHeap.push(5);
	testHeap.push(23);
	//testHeap.levelOrder(display);
	testHeap.pop();
	testHeap.pop();
	testHeap.levelOrder(display);
}
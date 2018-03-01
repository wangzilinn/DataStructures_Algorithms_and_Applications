#include "stdafx.h"
//数组描述的二叉树：
static void display(int * t)
{
	cout << *t << " ";
}

void testAt12()
{
	int n = 10;
	int* root = new int[2 * n]
	{ 20,12,35,15,10,80,30,17,2,31 };
	//maxHeap<int> testHeap(root, n);
	//testHeap.levelOrder(display);
	int* root2 = new int[2 * n]
	{ 20,12,35,15,10,80,30,17,2,9 };
	minHeap<int> testHeap2(root2, n);
	testHeap2.levelOrder(display);
	testHeap2.pop();
	cout << endl;
	testHeap2.levelOrder(display);
}
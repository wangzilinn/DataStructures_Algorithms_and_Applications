#include "stdafx.h"
//数组描述的二叉树：
static void display(int * t)
{
	cout << *t << " ";
}

void testAt12()
{
	int n = 7;
	int* root = new int[n + 1]
	{ 0,1,2,3,4,5,6,7 };//默认初始化
	completeBinaryTree<int> testTree(root, n);
	//cout << testTree.height();
	testTree.preOrder(display);
	cout << endl;
	testTree.inOrder(display);
	cout << endl;
	testTree.postOrder(display);
	cout << endl;
	testTree.levelOrder(display);
}
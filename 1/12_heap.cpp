#include "stdafx.h"
//���������Ķ�������
static void display(int * t)
{
	cout << *t << " ";
}

void testAt12()
{
	int n = 7;
	int* root = new int[n + 1]
	{ 0,1,2,3,4,5,6,7 };//Ĭ�ϳ�ʼ��
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
#include "stdafx.h"
void output(binaryTreeNode<int>* node)
{
	cout << node->element;
}
void TestAt11()
{
	//������
	binaryTreeNode<int> gL1(4);
	binaryTreeNode<int> gR1(5);
	binaryTreeNode<int> gL2(6);
	binaryTreeNode<int> gR2(7);
	binaryTreeNode<int> L(2, &gL1, &gR1);
	binaryTreeNode<int> R(3, &gL2, &gR2);
	binaryTreeNode<int> root(1, &L, &R);
	//װ����
	linkedBinaryTree<int> testTree(&root);
	cout << "�������" << endl;
	testTree.postOrder(output);
	cout << "ǰ�����" << endl;
	testTree.preOrder(output);
	cout << "�������" << endl;
	testTree.inOrder(output);
	cout << "��α���" << endl;
	testTree.levelOrder(output);
}
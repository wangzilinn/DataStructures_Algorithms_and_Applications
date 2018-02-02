#include "stdafx.h"
void output(binaryTreeNode<int>* node)
{
	cout << node->element;
}
void TestAt11()
{
	//构造树
	binaryTreeNode<int> gL1(4);
	binaryTreeNode<int> gR1(5);
	binaryTreeNode<int> gL2(6);
	binaryTreeNode<int> gR2(7);
	binaryTreeNode<int> L(2, &gL1, &gR1);
	binaryTreeNode<int> R(3, &gL2, &gR2);
	binaryTreeNode<int> root(1, &L, &R);
	//装载树
	linkedBinaryTree<int> testTree(&root);
	cout << "后序遍历" << endl;
	testTree.postOrder(output);
	cout << "前序遍历" << endl;
	testTree.preOrder(output);
	cout << "中序遍历" << endl;
	testTree.inOrder(output);
	cout << "层次遍历" << endl;
	testTree.levelOrder(output);
}
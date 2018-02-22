#include "stdafx.h"
void testAt15()
{
	binaryTreeNode<pair<int, string>> d(make_pair(12, "d"));
	binaryTreeNode<pair<int, string>> e(make_pair(18, "e"));
	binaryTreeNode<pair<int, string>> f(make_pair(30, "f"));
	binaryTreeNode<pair<int, string>> b(make_pair(15, "b"), &d, &e);
	binaryTreeNode<pair<int, string>> c(make_pair(25, "c"), nullptr, &f);
	binaryTreeNode<pair<int, string>> a(make_pair(20, "a"), &b, &c);
	BalanceBinarySearchTree<int, string> testTree(&a);
	testTree.ascend();
}
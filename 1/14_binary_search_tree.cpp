#include "stdafx.h"

void testAt14()
{
	//¹¹Ôì¶þ²æËÑË÷Ê÷
	binaryTreeNode<pair<int, string>> j(make_pair(31, "j"));
	binaryTreeNode<pair<int, string>> k(make_pair(33, "k"));
	binaryTreeNode<pair<int, string>> h(make_pair(60, "h"));
	binaryTreeNode<pair<int, string>> i(make_pair(85, "i"));
	binaryTreeNode<pair<int, string>> d(make_pair(2, "d"));
	binaryTreeNode<pair<int, string>> g(make_pair(32, "g"), &j, &k);
	binaryTreeNode<pair<int, string>> e(make_pair(35, "e"), &g, nullptr);
	binaryTreeNode<pair<int, string>> f(make_pair(80, "f"), &h, &i);
	binaryTreeNode<pair<int, string>> c(make_pair(40, "c"), &e, &f);
	binaryTreeNode<pair<int, string>> b(make_pair(5, "b"), &d, nullptr);
	binaryTreeNode<pair<int, string>> a(make_pair(30, "a"), &b, &c);
	BinarySearchTree<int, string> testTree(&a);
	testTree.insert(make_pair(1, "test"));
	testTree.insert(make_pair(37, "test2"));
	cout << testTree.find(2);
}
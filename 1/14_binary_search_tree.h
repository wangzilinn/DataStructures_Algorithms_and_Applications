#pragma once
void testAt14();
template <class K, class V>
class BinarySearchTree:public linkedBinaryTree<pair<K, V>>
{
private:

public:
	BinarySearchTree(binaryTreeNode<pair<K, V>>* theRoot) :linkedBinaryTree<pair<K, V>>(theRoot) {}
	BinarySearchTree() :linkedBinaryTree<pair<K, V>>() {}
	V find(const K theKey)const;
	void insert(pair<K, V> thePair);
	void earse(K theKey);
	void ascend() { linkedBinaryTree<pair<K, V>>::inOrder(output11); }
};
template <class K,class V>
V BinarySearchTree<K, V>::find(const K theKey) const
{
}
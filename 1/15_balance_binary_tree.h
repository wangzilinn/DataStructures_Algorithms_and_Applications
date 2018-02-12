#pragma once
void testAt15();
template <class K, class V>
class BalanceBinarySearchTree :public BinarySearchTree<K, V>
{
public:
	BalanceBinarySearchTree(binaryTreeNode<pair<K, V>> *theRoot) :BinarySearchTree<K, V>(theRoot) {}
	BalanceBinarySearchTree() :BinarySearchTree<K, V>() {}
	void insert(const pair<K, V>& thePair);
	void earse(const K& theKey);
};
template <class K, class V>
void BalanceBinarySearchTree<K, V>::insert(const pair<K, V>& thePair)
{
	BinarySearchTree<K, V>::insert(thePair);
	//»Ö¸´Æ½ºâ
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::earse(const K& theKey)
{
	BinarySearchTree<K, V>::earse(theKey);
	//»Ö¸´Æ½ºâ
}
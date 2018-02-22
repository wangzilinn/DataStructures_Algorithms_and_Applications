#pragma once
void testAt15();
template <class K, class V>
class BalanceBinarySearchTree :public BinarySearchTree<K, V>
{
private:
	//之所以使用静态函数是因为调用该函数的遍历函数是静态的
	//而静态函数只能调用静态函数
	static void initBf(binaryTreeNode<pair<K, V>>* theRoot)
	{
		int leftHeight = 0,rightHeight = 0;
		if (theRoot->leftChild != nullptr)
			leftHeight = theRoot->leftChild->height;
		if (theRoot->rightChild != nullptr)
			rightHeight = theRoot->rightChild->height;
		theRoot->nodeData = leftHeight - rightHeight;
	}
public:
	BalanceBinarySearchTree(binaryTreeNode<pair<K, V>> *theRoot) :BinarySearchTree<K, V>(theRoot) 
	{
		//新建的树,为每个节点计算平衡因子	
		postOrder(initBf);//postOrder继承自linkedBinaryTree
	}
	BalanceBinarySearchTree() :BinarySearchTree<K, V>() {}
	void insert(const pair<K, V>& thePair);
	void earse(const K& theKey);
	void ascend()
	{
		linkedBinaryTree<pair<K, V>>::inOrder(outputAVL);
	}
};
template <class K, class V>
void BalanceBinarySearchTree<K, V>::insert(const pair<K, V>& thePair)
{
	binaryTreeNode<pair<K, V>>* pointer = root;
	binaryTreeNode<pair<K, V>>* supPointer;//查找指针的父亲
	binaryTreeNode<pair<K, V>>* newOne = new binaryTreeNode<pair<K, V>>(thePair);
	CircularArrayQuene<binaryTreeNode<pair<K, V>>*> quene;//记录从根到所找到节点的路径
	while (pointer != nullptr)
	{
		supPointer = pointer;
		if (pointer->element.first == thePair.first)
		{
			pointer->element.second = thePair.second;
			delete newOne;
			return;//找到了相同的元素,直接返回
		}
		else if (thePair.first > pointer->element.first)
		{
			quene.push(pointer);
			pointer = pointer->rightChild;
		}
		else
		{
			quene.push(pointer);
			pointer = pointer->leftChild;
		}
	}
	if (thePair.first >= supPointer->element.first)
		supPointer->rightChild = newOne;
	else
		supPointer->leftChild = newOne;


	//恢复平衡
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::earse(const K& theKey)
{
	BinarySearchTree<K, V>::earse(theKey);
	//恢复平衡
}
template <class K, class V>
static void outputAVL(binaryTreeNode<pair<K, V>>* theNodePointer)
{
	cout << theNodePointer->element.first << ":" << theNodePointer->element.second 
		 << " height:" << theNodePointer->height << " bf:" << theNodePointer->nodeData << endl;
}
#pragma once
void testAt14();
template <class K, class V>
class BinarySearchTree:public linkedBinaryTree<pair<K, V>>
{
private:
	binaryTreeNode<pair<K, V>>* search(const K& theKey) const;
public:
	BinarySearchTree(binaryTreeNode<pair<K, V>>* theRoot) :linkedBinaryTree<pair<K, V>>(theRoot) {}
	BinarySearchTree() :linkedBinaryTree<pair<K, V>>() {}
	V find(const K& theKey)const;//complete
	void insert(const pair<K, V> thePair);//complete
	void earse(const K& theKey);//comlete
	void ascend() { linkedBinaryTree<pair<K, V>>::inOrder(output); }//complete
};
template <class K, class V>
binaryTreeNode<pair<K, V>>* BinarySearchTree<K, V>::search(const K& theKey)const
{
	binaryTreeNode<pair<K, V>> * pointer = root;
	while (pointer != nullptr)
	{
		if (theKey == pointer->element.first)
		{
			return pointer;
		}
		else if (theKey >= pointer->element.first)
		{
			pointer = pointer->rightChild;
		}
		else
		{
			pointer = pointer->leftChild;
		}
	}
	return nullptr;
}
template <class K,class V>
V BinarySearchTree<K, V>::find(const K &theKey) const
{
	binaryTreeNode<pair<K, V>>* result = search(theKey);
	if (result != nullptr)
	{
		return result->element.second;
	}
	else
		return "no result";
}
template <class K, class V>
void BinarySearchTree<K, V>::earse(const K& theKey)
{
	binaryTreeNode<pair<K, V>>* pointer = root;
	binaryTreeNode<pair<K, V>>* lastPointer = nullptr;
	while (pointer != nullptr)//查找要删除的节点和要删除节点的父亲
	{
		if (pointer->element.first == theKey)
		{
			break;
		}
		else if (theKey >= pointer->element.first)
		{
			lastPointer = pointer;
			pointer = pointer->rightChild;
		}
		else
		{
			lastPointer = pointer;
			pointer = pointer->leftChild;
		}
	}
	if (pointer == nullptr)
		return;//没找到元素
	//判断要删除节点的三种情况：
	//1.要删除的节点是叶子结点
	if (pointer->rightChild == nullptr && pointer->leftChild == nullptr)
	{
		if (lastPointer->leftChild->element.first == theKey)
			lastPointer->leftChild = nullptr;
		else
			lastPointer->rightChild = nullptr;
	}
	//2.1要删除的节点右子树为空
	else if (pointer->leftChild != nullptr && pointer->rightChild == nullptr)
	{
		lastPointer->leftChild = pointer->leftChild;
	}
	//2.2要删除节点的左子树为空
	else if (pointer->rightChild != nullptr && pointer->leftChild == nullptr)
	{
		lastPointer->rightChild = pointer->rightChild;
	}
	//3.要删除节点的左右子树都不空
	else//令其左子树最大节点替换该节点
	{
		//查找左子树最大节点：
		binaryTreeNode<pair<K, V>>* leftSubtreeMaxNode = pointer->leftChild;//左子树最大节点
		binaryTreeNode<pair<K, V>>* leftSubtreeMaxNodeFather = pointer;//左子树最大节点的父亲
		while (leftSubtreeMaxNode->rightChild != nullptr)
		{
			leftSubtreeMaxNodeFather = leftSubtreeMaxNode;
			leftSubtreeMaxNode = leftSubtreeMaxNode->rightChild;//不断向右查找直到为nullptr
		}
		//将找到的节点复制到删除节点处
		pointer->element = leftSubtreeMaxNode->element;
		//删除左子树最大节点(删除指向该节点的指针,如果该节点有左子树,则子树继承原来的位置)
		//之所以没有直接删除leftSubtreeMaxNodeFather的右节点是因为存在"左子树最大节点就是其左子树根"的情况,
		//该情况下,leftSubtreeMaxNode是leftSubtreeMaxNodeFather的左节点
		if (leftSubtreeMaxNodeFather->leftChild->element == leftSubtreeMaxNode->element)
		{
			if (leftSubtreeMaxNode->leftChild != nullptr)
				leftSubtreeMaxNodeFather->leftChild = leftSubtreeMaxNode->leftChild;
			else
				leftSubtreeMaxNodeFather->leftChild = nullptr;
		}
		else
		{
			if (leftSubtreeMaxNode->leftChild != nullptr)
				leftSubtreeMaxNodeFather->rightChild = leftSubtreeMaxNode->leftChild;
			else
				leftSubtreeMaxNodeFather->rightChild = nullptr;
		}
		//如果被选中的最大子节点有左子树,由于被找到的节点要么没有孩子,要么只有左孩子
		//所以让被找到的左子树的最大节点的父亲指向被找到的左子树的最大节点的左孩子
		
	}
}
template <class K, class V>
void BinarySearchTree<K, V>::insert(const pair<K, V> thePair)
{
	binaryTreeNode<pair<K, V>>* newOne = new binaryTreeNode<pair<K, V>>(thePair);
	binaryTreeNode<pair<K, V>>* pointer = root;
	binaryTreeNode<pair<K, V>>* finalPointer = nullptr;
	while (pointer != nullptr)
	{
		if (newOne->element.first == pointer->element.first)
		{
			pointer->element.second = newOne->element.second;
			return;
		}
		else if (newOne->element.first >= pointer->element.first)
		{
			finalPointer = pointer;//记录pointer的上一个指针，为了下面操作赋值
			pointer = pointer->rightChild;
		}
		else
		{
			finalPointer = pointer;//记录pointer的上一个指针，为了下面操作赋值
			pointer = pointer->leftChild;
		}
	}
	if (newOne->element.first >= finalPointer->element.first)
	{
		finalPointer->rightChild = newOne;
	}
	else
	{
		finalPointer->leftChild = newOne;
	}
}
template <class K, class V>
static void output(binaryTreeNode<pair<K, V>>* theNodePointer)
{
	cout << theNodePointer->element.first << ":" << theNodePointer->element.second << "  ";
}
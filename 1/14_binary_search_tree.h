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
	void earse(const K& theKey);
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
	while (pointer != nullptr)
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
	if (pointer->rightChild == nullptr && pointer->leftChild == nullptr)//要删除的节点是叶子结点
	{
		if (lastPointer->leftChild.first == theKey)
			lastPointer->leftChild = nullptr;
		else
			lastPointer->rightChild = nullptr;
	}
	else if (pointer->leftChild != nullptr && pointer->rightChild == nullptr)//要删除的节点右子树为空
	{
		lastPointer->leftChild = pointer->leftChild;
	}
	else if (pointer->rightChild != nullptr && pointer->leftChild == nullptr)//要删除的节点左子树为空
	{
		lastPointer->rightChild = pointer->rightChild;
	}
	else//被删除的节点左右子树都不为空,令其左子树????最大节点替换该节点
	{
		//查找左子树最大节点：
		binaryTreeNode<pair<K, V>> searchPointer = pointer->leftChild;
		binaryTreeNode<pair<K, V>> leftMaxChildsFather = pointer;//左子树最大节点的父亲
		while (searchPointer->rightChild != nullptr)
		{
			leftMaxChildsFather = searchPointer;
			searchPointer = searchPointer->rightChild;//不断向右查找直到为nullptr
		}
		if (lastPointer != nullptr)//当删除的不是根节点时：
		{
			if (lastPointer->leftChild.first == theKey)
			{
				lastPointer->leftChild = searchPointer;
				if (searchPointer->leftChild != nullptr)//被选中的最大子节点有左子树时
				{//比较该左子树和被删除节点左子树哪个小，确定左右子树的分配
					if (searchPointer->leftChild.first >= pointer->leftChild.first)
					{
						searchPointer->rightChild = searchPointer->leftChild;
						searchPointer->leftChild = pointer->leftChild;
					}
					else
					{
						searchPointer->rightChild = pointer->leftChild;
					}
				}
				else
					searchPointer->leftChild = pointer->leftChild;//当没有左子树时，被选中节点左子树直接指向被删除节点左子树
			}
			else
			{
				lastPointer->rightChild = searchPointer;
				if (searchPointer->leftChild != nullptr)
				{
					if (searchPointer->leftChild.first >= pointer->leftChild.first)
					{

					}
				}
			}
		}
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
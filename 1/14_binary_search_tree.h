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
		return;//û�ҵ�Ԫ��
	//�ж�Ҫɾ���ڵ�����������
	if (pointer->rightChild == nullptr && pointer->leftChild == nullptr)//Ҫɾ���Ľڵ���Ҷ�ӽ��
	{
		if (lastPointer->leftChild.first == theKey)
			lastPointer->leftChild = nullptr;
		else
			lastPointer->rightChild = nullptr;
	}
	else if (pointer->leftChild != nullptr && pointer->rightChild == nullptr)//Ҫɾ���Ľڵ�������Ϊ��
	{
		lastPointer->leftChild = pointer->leftChild;
	}
	else if (pointer->rightChild != nullptr && pointer->leftChild == nullptr)//Ҫɾ���Ľڵ�������Ϊ��
	{
		lastPointer->rightChild = pointer->rightChild;
	}
	else//��ɾ���Ľڵ�������������Ϊ��,����������????���ڵ��滻�ýڵ�
	{
		//�������������ڵ㣺
		binaryTreeNode<pair<K, V>> searchPointer = pointer->leftChild;
		binaryTreeNode<pair<K, V>> leftMaxChildsFather = pointer;//���������ڵ�ĸ���
		while (searchPointer->rightChild != nullptr)
		{
			leftMaxChildsFather = searchPointer;
			searchPointer = searchPointer->rightChild;//�������Ҳ���ֱ��Ϊnullptr
		}
		if (lastPointer != nullptr)//��ɾ���Ĳ��Ǹ��ڵ�ʱ��
		{
			if (lastPointer->leftChild.first == theKey)
			{
				lastPointer->leftChild = searchPointer;
				if (searchPointer->leftChild != nullptr)//��ѡ�е�����ӽڵ���������ʱ
				{//�Ƚϸ��������ͱ�ɾ���ڵ��������ĸ�С��ȷ�����������ķ���
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
					searchPointer->leftChild = pointer->leftChild;//��û��������ʱ����ѡ�нڵ�������ֱ��ָ��ɾ���ڵ�������
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
			finalPointer = pointer;//��¼pointer����һ��ָ�룬Ϊ�����������ֵ
			pointer = pointer->rightChild;
		}
		else
		{
			finalPointer = pointer;//��¼pointer����һ��ָ�룬Ϊ�����������ֵ
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
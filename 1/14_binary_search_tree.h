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
	while (pointer != nullptr)//����Ҫɾ���Ľڵ��Ҫɾ���ڵ�ĸ���
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
	//1.Ҫɾ���Ľڵ���Ҷ�ӽ��
	if (pointer->rightChild == nullptr && pointer->leftChild == nullptr)
	{
		if (lastPointer->leftChild->element.first == theKey)
			lastPointer->leftChild = nullptr;
		else
			lastPointer->rightChild = nullptr;
	}
	//2.1Ҫɾ���Ľڵ�������Ϊ��
	else if (pointer->leftChild != nullptr && pointer->rightChild == nullptr)
	{
		lastPointer->leftChild = pointer->leftChild;
	}
	//2.2Ҫɾ���ڵ��������Ϊ��
	else if (pointer->rightChild != nullptr && pointer->leftChild == nullptr)
	{
		lastPointer->rightChild = pointer->rightChild;
	}
	//3.Ҫɾ���ڵ����������������
	else//�������������ڵ��滻�ýڵ�
	{
		//�������������ڵ㣺
		binaryTreeNode<pair<K, V>>* leftSubtreeMaxNode = pointer->leftChild;//���������ڵ�
		binaryTreeNode<pair<K, V>>* leftSubtreeMaxNodeFather = pointer;//���������ڵ�ĸ���
		while (leftSubtreeMaxNode->rightChild != nullptr)
		{
			leftSubtreeMaxNodeFather = leftSubtreeMaxNode;
			leftSubtreeMaxNode = leftSubtreeMaxNode->rightChild;//�������Ҳ���ֱ��Ϊnullptr
		}
		//���ҵ��Ľڵ㸴�Ƶ�ɾ���ڵ㴦
		pointer->element = leftSubtreeMaxNode->element;
		//ɾ�����������ڵ�(ɾ��ָ��ýڵ��ָ��,����ýڵ���������,�������̳�ԭ����λ��)
		//֮����û��ֱ��ɾ��leftSubtreeMaxNodeFather���ҽڵ�����Ϊ����"���������ڵ��������������"�����,
		//�������,leftSubtreeMaxNode��leftSubtreeMaxNodeFather����ڵ�
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
		//�����ѡ�е�����ӽڵ���������,���ڱ��ҵ��Ľڵ�Ҫôû�к���,Ҫôֻ������
		//�����ñ��ҵ��������������ڵ�ĸ���ָ���ҵ��������������ڵ������
		
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
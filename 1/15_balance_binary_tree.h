#pragma once
void testAt15();
template <class K, class V>
class BalanceBinarySearchTree :public BinarySearchTree<K, V>
{
private:
	//֮����ʹ�þ�̬��������Ϊ���øú����ı��������Ǿ�̬��
	//����̬����ֻ�ܵ��þ�̬����
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
		//�½�����,Ϊÿ���ڵ����ƽ������	
		postOrder(initBf);//postOrder�̳���linkedBinaryTree
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
	enum
	{
		left,
		right
	}direction;
	binaryTreeNode<pair<K, V>>* pointer = root;
	binaryTreeNode<pair<K, V>>* supPointer = nullptr;//����ָ��ĸ���
	binaryTreeNode<pair<K, V>>* pointerA = nullptr;//ָ��ƽ������Ϊ1��-1�Ľڵ�
	binaryTreeNode<pair<K, V>>* supPointerA = nullptr;//ָ��ڵ�A�ĸ���
	binaryTreeNode<pair<K, V>>* newOne = new binaryTreeNode<pair<K, V>>(thePair);
	linkedStack<binaryTreeNode<pair<K, V>>*> stack;//��¼�Ӹ������ҵ��ڵ��·��
	//����ڵ�
	while (pointer != nullptr)
	{
		supPointer = pointer;
		if (pointer->element.first == thePair.first)
		{
			pointer->element.second = thePair.second;
			delete newOne;
			return;//�ҵ�����ͬ��Ԫ��,ֱ�ӷ���
		}
		else if (thePair.first > pointer->element.first)
		{
			stack.push(pointer);
			if ((pointer->nodeData == 1) || (pointer->nodeData == -1))
			{
				supPointerA = pointerA;
				pointerA = pointer;
			}
			pointer = pointer->rightChild;
		}
		else
		{
			stack.push(pointer);
			if ((pointer->nodeData == 1) || (pointer->nodeData == -1))
			{
				supPointerA = pointerA;
				pointerA = pointer;
			}			
			pointer = pointer->leftChild;
		}
	}
	if (thePair.first >= supPointer->element.first)
	{
		supPointer->rightChild = newOne;
		direction = right;
	}
	else
	{
		supPointer->leftChild = newOne;
		direction = left;
	}
	//���A�ڵ��Ƿ����:ע��,��ʱpointerAָ��������һ������������A
	if (pointerA == nullptr)//�ڵ�A������->ԭ���������߶����->ֱ�����,�������ߺ�ƽ������
	{
		//����ջ�нڵ�
		while (!stack.empty())
		{
			pointer = stack.top();
			stack.pop();
			pointer->height++;
			int leftHeight = 0, rightHeight = 0;
			if (pointer->leftChild != nullptr)
				leftHeight = pointer->leftChild->height;
			if (pointer->rightChild != nullptr)
				rightHeight = pointer->rightChild->height;
			pointer->nodeData = leftHeight - rightHeight;
		}
	}
	else if ((pointerA->leftChild == newOne) || (pointer->rightChild == newOne))
	{
		pointerA->nodeData = 0;//����ڵ�Aֱ�����²���Ľڵ�����,��ô˵���½ڵ������ڿ�λ��,��ʱ���½ڵ�A��ƽ�����Ӽ���,��������Ӱ��
	}
	else//��ʼ��ת
	{
		if ((pointerA->nodeData == -1) && (direction == right))
		{
			//RR
		}
		else if ((pointerA->nodeData == 1) && (direction == left))
		{
			//LL
		}
		else if ((pointer->nodeData == -1) && (direction == right))
		{
			//RL
		}
		else if ((pointer->nodeData == 1) && (direction == left))
		{
			//LR
		}
	}
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::earse(const K& theKey)
{
	BinarySearchTree<K, V>::earse(theKey);
	//�ָ�ƽ��
}
template <class K, class V>
static void outputAVL(binaryTreeNode<pair<K, V>>* theNodePointer)
{
	cout << theNodePointer->element.first << ":" << theNodePointer->element.second 
		 << " height:" << theNodePointer->height << " bf:" << theNodePointer->nodeData << endl;
}
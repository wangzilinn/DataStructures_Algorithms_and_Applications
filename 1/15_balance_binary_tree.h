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
	binaryTreeNode<pair<K, V>>* pointer = root;
	binaryTreeNode<pair<K, V>>* supPointer;//����ָ��ĸ���
	binaryTreeNode<pair<K, V>>* newOne = new binaryTreeNode<pair<K, V>>(thePair);
	CircularArrayQuene<binaryTreeNode<pair<K, V>>*> quene;//��¼�Ӹ������ҵ��ڵ��·��
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


	//�ָ�ƽ��
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
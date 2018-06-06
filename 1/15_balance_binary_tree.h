#pragma once
/*
ע��:AVL������ת��δд��,����Ϊ���Ѿ������AVL�����ں�,
������ʵ�ַ����ϳ�����ƫ��,���¹��̷������˷�ʱ��,���Ƚ�����һ��.
*/
void testAt15();
template <class K, class V>
class BalanceBinarySearchTree :public BinarySearchTree<K, V>
{
private:
	//֮����ʹ�þ�̬��������Ϊ���øú����ı��������Ǿ�̬��
	//��ֻ�о�̬�����ܵ��þ�̬����
	static void __InitBf(binaryTreeNode<pair<K, V>>* theRoot)//����ƽ������
	{
		int leftHeight = 0,rightHeight = 0;
		if (theRoot->leftChild != nullptr)
			leftHeight = theRoot->leftChild->height;
		if (theRoot->rightChild != nullptr)
			rightHeight = theRoot->rightChild->height;
		theRoot->bf = leftHeight - rightHeight;
	}
	bool __Insert(binaryTreeNode<pair<K, V>> *theRoot, const pair<K, V> &thePair, bool *taller);
	void __LRotate(binaryTreeNode<pair<K, V>> *theRoot);
	void __RRotate(binaryTreeNode<pair<K, V>> *theRoot);
	void __LeftBalance(binaryTreeNode<pair<K, V>> *theRoot);
	void __RightBalance(binaryTreeNode<pair<K, V>> *theRoot);
public:
	BalanceBinarySearchTree(binaryTreeNode<pair<K, V>> *theRoot) :BinarySearchTree<K, V>(theRoot) 
	{
		//�½�����,Ϊÿ���ڵ����ƽ������	
		postOrder(__InitBf);//postOrder�̳���linkedBinaryTree
	}
	BalanceBinarySearchTree() :BinarySearchTree<K, V>() {}
	void Insert(const pair<K, V>& thePair)
	{
		bool taller = true;
		__Insert(root, thePair, &taller);
	}
	void Earse(const K& theKey);
	void Ascend()//�˱�������û��ʹ�ü̳��Զ����������ı��������������½���һ����Ϊ���Ǹ�ȫ�����ʾƽ��������Ľ����Ϣ
	{
		linkedBinaryTree<pair<K, V>>::inOrder(outputAVL);
	}
};
template <class K,class V>
void BalanceBinarySearchTree<K, V>::__RRotate(binaryTreeNode<pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>>* newRoot = theRoot->rightChild;//����һ����ʱָ��ָ���µĸ��ڵ�(ԭ���������Һ��ӣ�
	theRoot->rightChild = newRoot->leftChild;//�Ƚ��¸��ڵ�������и���ԭ���ĸ��ڵ�
	newRoot->leftChild = theRoot;//�ٽ�ԭ���ĸ��ڵ���������Ϊ�¸��ڵ������
	theRoot = newRoot;//�����µĸ����
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::__LRotate(binaryTreeNode<pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>>* newRoot = theRoot->leftChild;//����һ����ʱָ��ָ���µĸ���㣨ԭ�����������ӣ�
	theRoot->leftChild = newRoot->rightChild;//���µĸ����������и���ԭ������㣨��Ϊԭ���������Һ��ӣ�
	newRoot->rightChild = theRoot;//��ԭ���������������Ϊ�¸��ڵ���Һ���
	theRoot = newRoot;//�����µĸ����
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::__LeftBalance(binaryTreeNode <pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>>* leftChild = theRoot->leftChild;
	if (leftChild->bf = 1)//�²����������ӵ���������(LL)
	{
		theRoot->bf = 0;//ԭ���ĸ�������Ϊ�Һ��ӣ����ǵȸߵ�
		__RRotate(theRoot);//�ƶ����µĸ����
		theRoot->bf = 0;//�µĸ����Ҳ�ǵȸߵ�
	}
	else if (leftChild->bf = -1)//�²���Ľ�������ӵ��������ϣ�LR��
	{
		//����ע�⣺���渳��bfֵ����ת֮�������ֵ������������δ��ת�����Ը�����Щֵ��ָ�뻹��ԭ���ġ�
		switch (leftChild->rightChild->bf)//��ͼ��������������ת�����֮���ƽ��״̬
		{
		case 1://�½���ڸ��������ӵ��Һ��ӵ���ߣ���һ����ת�󱻸�������������
			theRoot->bf = -1;
			leftChild->bf = 0;
			break;
		case 0://�½����Ǹ��������ӵ��Һ���
			theRoot->bf = 0;
			leftChild->bf = 0;
			break;
		case -1://�½���ڸ���������ӵ��Һ��ӵ��ұ�
			theRoot->bf = 0;
			leftChild->bf = 1;
			break;
		}
		leftChild->rightChild->bf = 0;//ͬ�ϡ�ע�⡱�����а�ƽ�����Ӹ���
		__LRotate(theRoot->leftChild);
		__RRotate(theRoot);
	}
	else
		throw "fuck";
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::__RightBalance(binaryTreeNode<pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>> rightChild = theRoot->rightChild;
	if (rightChild->bf = -1)
	{
		theRoot->bf = 0;
		rightChild->bf = 0;
		__LRotate(theRoot);
		break;
	}
	else if (rightChild->bf = 1)
	{
		switch (rightChild->leftChild->bf)
		{
		case -1:
			theRoot->bf = 1;
			rightChild->bf = 0;
			break;
		case 0:
			theRoot->bf = 0;
			rightChild->bf = 0;
			break;
		case 1:
			theRoot->bf = 0;
			rightChild->bf = -1;
			break;
		}
		rightChild->leftChild->bf = 0;
		__RRotate(theRoot->rightChild);
		__LRotate(theRoot);
	}
	else
		throw "fuck"
}
template <class K, class V>
bool BalanceBinarySearchTree<K, V>::__Insert(binaryTreeNode<pair<K, V>> *theRoot, const pair<K, V> &thePair, bool *taller)
{
	if (theRoot == nullptr)//�ݹ鵽����ˣ�����ڵ�
	{
		theRoot = new binaryTreeNode(thePair);
		theRoot->bf = 0;
		*taller = true;
	}
	else//��ʼ���бȽ�
	{
		if (thePair.first == theRoot->element.first)
		{
			*taller = false;
			return false;
		}
		if (thePair.first < theRoot->element.first)//Ҫ�����С�ڵ�ǰ���
		{
			//��thePai��theRoot���������в���
			if (__Insert(theRoot->leftChild, thePair, taller) == false)//���µ��øú������Ѹ�����Ϊ������
				return false;
			if (*taller == true)//�������֮������������
			{
				switch (theRoot->bf)
				{
				case 1://ԭ����߾͸ߣ��ָ���һ�㣬�϶���ƽ����
					__LeftBalance(theRoot);
					break;
				case 0:
					theRoot->bf = 1;//ԭ��һ���ߣ���Ϊ�ֲ�����һ����������߸���
					*taller = true;
					break;
				case -1:
					theRoot->bf = 0;//ԭ���ұ߸ߣ�����һ��֮��һ������
					*taller = false;
					break;
				default:
					break;
				}
			}
		}
		else//thePair.first > theRoot->element.first Ҫ����Ĵ��ڵ�ǰ���
		{
			if (__Insert(theRoot->rightChild, thePair, taller) == false)
				return false;
			if (*taller)
			{
				case 1:
					theRoot->bf = 0;
					*taller = false;
					break;
				case 0:
					theRoot->bf = -1;
					*taller = true;
					break;
				case -1:
					__RightBalance(theRoot);
					break;
				default:
					break;
			}
		}
	}
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::Earse(const K& theKey)
{
	BinarySearchTree<K, V>::earse(theKey);
	//�ָ�ƽ��
}
template <class K, class V>
static void outputAVL(binaryTreeNode<pair<K, V>>* theNodePointer)
{
	cout << theNodePointer->element.first << ":" << theNodePointer->element.second 
		 << " height:" << theNodePointer->height << " bf:" << theNodePointer->bf << endl;
}
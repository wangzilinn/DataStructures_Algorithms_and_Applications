#pragma once
/*
注意:AVL数在旋转处未写完,我认为我已经理解了AVL数的内涵,
但是在实现方法上出现了偏差,导致过程繁杂且浪费时间,故先进行下一节.
*/
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
	enum
	{
		left,
		right
	}direction/*添加的节点是左子树还是右子树*/,directionA/*A是左子树还是右子树*/;
	binaryTreeNode<pair<K, V>>* pointer = root;
	binaryTreeNode<pair<K, V>>* supPointer = nullptr;//查找指针的父亲
	binaryTreeNode<pair<K, V>>* pointerA = nullptr;//指向平衡因子为1或-1的节点
	binaryTreeNode<pair<K, V>>* supPointerA = nullptr;//指向节点A的父亲
	binaryTreeNode<pair<K, V>>* newOne = new binaryTreeNode<pair<K, V>>(thePair);
	linkedStack<binaryTreeNode<pair<K, V>>*> stack;//记录从根到所找到节点的路径
	//插入节点
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
			stack.push(pointer);
			if ((pointer->nodeData == 1) || (pointer->nodeData == -1))
			{
				supPointerA = pointerA;
				pointerA = pointer;
				directionA = right;
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
				directionA = left;
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
	//检查A节点是否存在:注意,此时pointerA指向的是最后一个满足条件的A
	//此时栈中的存放的是从"根节点"到"添加节点的父节点"的所有节点
	if (pointerA == nullptr)//节点A不存在->原来的子树高度相等->直接添加,更新树高和平衡因子
	{
		//更新栈中节点
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
		pointerA->nodeData = 0;//如果节点A直接与新插入的节点相连,那么说明新节点正好在空位上,此时更新节点A的平衡因子即可,对树高无影响
	}
	else//开始旋转
	{
		if ((pointerA->nodeData == -1) && (direction == right))
		{
			if (directionA == right)
			{
				supPointerA->rightChild = supPointer;
				supPointer->leftChild = pointerA;
				//将pointerA变成叶子
				pointerA->leftChild = nullptr;
				pointerA->rightChild = nullptr;
				pointerA->height = 1;
				pointerA->nodeData = 0;
			}
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
	//恢复平衡
}
template <class K, class V>
static void outputAVL(binaryTreeNode<pair<K, V>>* theNodePointer)
{
	cout << theNodePointer->element.first << ":" << theNodePointer->element.second 
		 << " height:" << theNodePointer->height << " bf:" << theNodePointer->nodeData << endl;
}
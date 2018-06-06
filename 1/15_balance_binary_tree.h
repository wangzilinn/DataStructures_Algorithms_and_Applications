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
	//而只有静态函数能调用静态函数
	static void __InitBf(binaryTreeNode<pair<K, V>>* theRoot)//计算平衡因子
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
		//新建的树,为每个节点计算平衡因子	
		postOrder(__InitBf);//postOrder继承自linkedBinaryTree
	}
	BalanceBinarySearchTree() :BinarySearchTree<K, V>() {}
	void Insert(const pair<K, V>& thePair)
	{
		bool taller = true;
		__Insert(root, thePair, &taller);
	}
	void Earse(const K& theKey);
	void Ascend()//此遍历函数没有使用继承自二叉搜索树的遍历函数，而是新建了一个，为的是更全面的显示平衡二叉树的结点信息
	{
		linkedBinaryTree<pair<K, V>>::inOrder(outputAVL);
	}
};
template <class K,class V>
void BalanceBinarySearchTree<K, V>::__RRotate(binaryTreeNode<pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>>* newRoot = theRoot->rightChild;//创建一个临时指针指向新的根节点(原来根结点的右孩子）
	theRoot->rightChild = newRoot->leftChild;//先将新根节点的左孩子托付给原来的根节点
	newRoot->leftChild = theRoot;//再将原来的根节点左旋，作为新根节点的左孩子
	theRoot = newRoot;//返回新的根结点
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::__LRotate(binaryTreeNode<pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>>* newRoot = theRoot->leftChild;//创建一个临时指针指向新的根结点（原来根结点的左孩子）
	theRoot->leftChild = newRoot->rightChild;//将新的根结点的左孩子托付给原来根结点（作为原来根结点的右孩子）
	newRoot->rightChild = theRoot;//将原来根结点右旋，作为新根节点的右孩子
	theRoot = newRoot;//返回新的根结点
}
template <class K, class V>
void BalanceBinarySearchTree<K, V>::__LeftBalance(binaryTreeNode <pair<K, V>> *theRoot)
{
	binaryTreeNode<pair<K, V>>* leftChild = theRoot->leftChild;
	if (leftChild->bf = 1)//新插入结点在左孩子的左子树上(LL)
	{
		theRoot->bf = 0;//原来的根结点会作为右孩子，且是等高的
		__RRotate(theRoot);//移动到新的根结点
		theRoot->bf = 0;//新的根结点也是等高的
	}
	else if (leftChild->bf = -1)//新插入的结点在左孩子的右子树上（LR）
	{
		//以下注意：下面赋的bf值是旋转之后的最终值，但是由于尚未旋转，所以更新这些值得指针还是原来的。
		switch (leftChild->rightChild->bf)//看图才能清楚三种情况转换完成之后的平衡状态
		{
		case 1://新结点在根结点的左孩子的右孩子的左边，第一次旋转后被根结点的左孩子收养
			theRoot->bf = -1;
			leftChild->bf = 0;
			break;
		case 0://新结点就是根结点的左孩子的右孩子
			theRoot->bf = 0;
			leftChild->bf = 0;
			break;
		case -1://新结点在根结点在左孩子的右孩子的右边
			theRoot->bf = 0;
			leftChild->bf = 1;
			break;
		}
		leftChild->rightChild->bf = 0;//同上“注意”，先行把平衡因子更新
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
	if (theRoot == nullptr)//递归到最后了，插入节点
	{
		theRoot = new binaryTreeNode(thePair);
		theRoot->bf = 0;
		*taller = true;
	}
	else//开始进行比较
	{
		if (thePair.first == theRoot->element.first)
		{
			*taller = false;
			return false;
		}
		if (thePair.first < theRoot->element.first)//要插入的小于当前结点
		{
			//将thePai向theRoot的左子树中插入
			if (__Insert(theRoot->leftChild, thePair, taller) == false)//重新调用该函数，把根结点变为其左结点
				return false;
			if (*taller == true)//如果插入之后左子树长高
			{
				switch (theRoot->bf)
				{
				case 1://原本左边就高，又高了一层，肯定不平衡了
					__LeftBalance(theRoot);
					break;
				case 0:
					theRoot->bf = 1;//原本一样高，因为又插入了一个，所以左边高了
					*taller = true;
					break;
				case -1:
					theRoot->bf = 0;//原本右边高，插入一个之后一样高了
					*taller = false;
					break;
				default:
					break;
				}
			}
		}
		else//thePair.first > theRoot->element.first 要插入的大于当前结点
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
	//恢复平衡
}
template <class K, class V>
static void outputAVL(binaryTreeNode<pair<K, V>>* theNodePointer)
{
	cout << theNodePointer->element.first << ":" << theNodePointer->element.second 
		 << " height:" << theNodePointer->height << " bf:" << theNodePointer->bf << endl;
}
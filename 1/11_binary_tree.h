#pragma once
template<class T>
struct binaryTreeNode
{
	T element;
	int nodeData;//拓展之用
	int height = 1;//树高
	binaryTreeNode* leftChild;
	binaryTreeNode* rightChild;
	binaryTreeNode(const T theElement) :element(theElement), leftChild(nullptr), rightChild(nullptr){}
	binaryTreeNode() :leftChild(nullptr), rightChild(nullptr) {}
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
		:element(theElement), leftChild(theLeftChild), rightChild(theRightChild){}
};
//二叉树抽象类：
template <class T>
class binaryTree
{
public:
	virtual ~binaryTree() {}
	virtual bool empty() const = 0;
	virtual int height() const = 0;
	virtual void preOrder(void(*)(T*)) = 0;
	virtual void inOrder(void(*)(T*)) = 0;
	virtual void postOrder(void(*)(T*)) = 0;
	virtual void levelOrder(void(*)(T*)) = 0;
};
//链表描述的二叉树：
template<class T>
class linkedBinaryTree :public binaryTree<binaryTreeNode<T>>//这里注意模板类型的继承关系
{
protected:
	binaryTreeNode<T> * root;
	int treeHeight;
	static void (*visit)(binaryTreeNode<T>*);//静态类的static关键字只需要再类内写，在外部不需要写
	static void preOrder(binaryTreeNode<T>* t);
	static void inOrder(binaryTreeNode<T>* t);
	static void postOrder(binaryTreeNode<T> * t);
	static void levelOrder(binaryTreeNode<T> *t);
	static void dispose(binaryTreeNode<T> * t) {};
	static int height(binaryTreeNode<T> *t);
public:
	linkedBinaryTree() : root(nullptr), treeHeight(0) {}
	linkedBinaryTree(binaryTreeNode<T> * theRoot)
	{
		root = theRoot;
		treeHeight = height(root);
	}
	~linkedBinaryTree() { earse(); }
	bool empty() const { return treeHeight == 0; }
	void preOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		linkedBinaryTree<T>::visit = theVisit;
		preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		linkedBinaryTree<T>::visit = theVisit;
		inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		linkedBinaryTree<T>::visit = theVisit;
		postOrder(root);
	}
	void levelOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		linkedBinaryTree<T>::visit = theVisit;
		levelOrder(root);
	}
	void earse()
	{
		postOrder(dispose);//使用后续遍历删除节点，不用保存节点信息
		root = nullptr;
		treeHeight = 0;
	}
	int height() const { return height(root); }
};
template<class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t)
{
	if (t != nullptr)
	{
		linkedBinaryTree<T>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}
template <class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t)
{
	if (t != nullptr)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}
template <class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t)
{
	if (t != nullptr)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}
template <class T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T> *t)
{
	CircularArrayQuene<binaryTreeNode<T>*> quene;
	while (t != nullptr)//当非空时才进入循环，只有这一个作用
	{
		if (!quene.empty())
		{
			t = quene.pop();
		}
		visit(t);
		if (t->leftChild != nullptr)
		{
			quene.push(t->leftChild);
		}
		if (t->rightChild != nullptr)
		{
			quene.push(t->rightChild);
		}
		if (quene.empty())
		{
			return;
		}
	}
}
template <class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		int hl = height(t->leftChild);
		int hr = height(t->rightChild);
		t->height = (hl > hr ? ++hl : ++hr);
		return t->height;
	}
	else
	{
		return 0;
	}
}
void(*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*) = nullptr;//静态成员的初始化
void(*linkedBinaryTree<pair<int, string>>::visit)(binaryTreeNode<pair<int, string>>*) = nullptr;
void TestAt11();
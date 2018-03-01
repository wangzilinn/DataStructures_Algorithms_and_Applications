#pragma once
void testAt12();
//为了减少代码，假设数组长度总是足够的
template<class T>
class completeBinaryTree:public binaryTree<T>//这里注意模板类型的继承关系
{
protected:
	T * root;
	int n;
	void(*visit)(T*);
	int treeHeight;
	void inOrder(int index)
	{
		if (index <= n)
		{
			inOrder(index * 2);
			visit(&(root[index]));
			inOrder(index * 2 + 1);
		}
	}
	void preOrder(int index)
	{
		if (index <= n)
		{
			visit(&(root[index]));
			preOrder(index * 2);
			preOrder(index * 2 + 1);
		}
	}
	void postOrder(int index)
	{
		if (index <= n)
		{
			postOrder(index * 2);
			postOrder(index * 2 + 1);
			visit(&(root[index]));
		}
	}
	void resetHeight()
	{
		treeHeight = static_cast<int>(ceil(log10(n + 1) / log10(2)));
	}
public:
	completeBinaryTree(T* theRoot, int theN) :root(theRoot), n(theN) 
	{ 
		for (int i = n - 1; i >= 0; i--)//将数组往后移一位,因为在二叉树中下标0是没用的
		{
			root[i + 1] = root[i];
		}
		resetHeight(); 
	}
	completeBinaryTree() : root(nullptr), visit(nullptr) {}
	~completeBinaryTree()
	{
		delete[] root;
	}
	bool empty() const { return treeHeight == 0; }
	int height() const { return treeHeight; }
	void inOrder(void(*f)(T*));
	void preOrder(void(*f)(T*));
	void postOrder(void(*f)(T*));
	void levelOrder(void(*f)(T*));
};	
template<class T>
void completeBinaryTree<T>::inOrder(void(*f)(T*))
{
	visit = f;
	inOrder(1);
}
template<class T>
void completeBinaryTree<T>::preOrder(void(*f)(T*))
{
	visit = f;
	preOrder(1);
}
template <class T>
void completeBinaryTree<T>::postOrder(void(*f)(T*))
{
	visit = f;
	postOrder(1);
}
template <class T>
void completeBinaryTree<T>::levelOrder(void(*f)(T*))
{
	for (int i = 1; i <= n; i++)
	{
		f(&(root[i]));
	}
}
template <class T>
class maxHeap:public completeBinaryTree<T>//继承之前没有T
{
private:
	void initialize();
public:
	maxHeap(T* theRoot, int theN):completeBinaryTree<T>(theRoot, theN)
	{
		initialize();
	}
	void push(const T& theElement);
	T pop();//删除并返回最大元素
};
template <class T>
void maxHeap<T>::initialize()
{
	//从第一个有孩子的节点开始操作
	int pointer = n / 2;
	while (pointer != 0)
	{
		int childRoot = pointer;
		do
		{
			int leftChild = childRoot * 2;
			int rightChild = childRoot * 2 + 1;
			if (rightChild <= n)
			{
				if (root[leftChild] >= root[rightChild])
				{
					if (root[childRoot] < root[leftChild])
					{
						swap(root[childRoot], root[leftChild]);
						childRoot = leftChild;
					}
					else
						break;
				}
				else//右孩子大于左孩子
				{
					if (root[childRoot] < root[rightChild])
					{
						swap(root[childRoot], root[rightChild]);
						childRoot = rightChild;
					}
					else
						break;
				}
			}
			else//最后一个没有右孩子
			{
				if (root[childRoot] < root[leftChild])
				{
					swap(root[childRoot], root[leftChild]);
					childRoot = leftChild;
				}
				else
					break;
			}
		} 
		while (childRoot < n / 2);
		pointer--;
	}
}
template <class T>
void maxHeap<T>::push(const T& theElement)
{
	//先插入数组末尾，然后进行起泡操作
	root[++n] = theElement;
	int pointer = n;
	while (pointer != 1)
	{
		//找到他的父亲
		int father = pointer / 2;
		if (root[father] < root[pointer])
		{
			swap(root[father], root[pointer]);
		}
		pointer = father;
	}
}
template <class T>
T maxHeap<T>::pop()
{
	T toReturn = root[1];//取出根元素准备返回
	T compare = root[n--];
	int pointer = 1;
	do
	{
		root[pointer] = compare;
		int lChild = pointer * 2;
		int rChild = pointer * 2 + 1;
		if (root[lChild] >= root[rChild])//左孩子更大
		{
			swap(root[lChild], root[pointer]);
			pointer = lChild;
		}
		else//右孩子更大
		{
			swap(root[rChild], root[pointer]);
			pointer = rChild;
		}
	} 
	while (pointer < n / 2);
	return toReturn;
}
template <class T>
class minHeap :public completeBinaryTree<T>
{
private:
	void initialize();
public:
	minHeap(T* theRoot, int theN) :completeBinaryTree<T>(theRoot, theN)
	{
		initialize();
	}
	void push(const T& theElement);
	T pop();
};
template <class T>
void minHeap<T>::initialize()
{
	int pointer = n / 2;
	while (pointer != 0)
	{
		int childRoot = pointer;
		do
		{
			int leftChild = childRoot * 2;
			int rightChild = childRoot * 2 + 1;
			if (rightChild <= n)
			{
				if (root[leftChild] >= root[rightChild])
				{
					if (root[childRoot] > root[rightChild])
					{
						swap(root[childRoot], root[rightChild]);
						childRoot = rightChild;
					}
					else
						break;
				}
				else//左边的孩子更小
				{
					if (root[childRoot] > root[leftChild])
					{
						swap(root[childRoot], root[leftChild]);
						childRoot = leftChild;
					}
					else
						break;
				}
			}
			else
			{
				if (root[childRoot] > root[leftChild])
				{
					swap(root[childRoot], root[leftChild]);
				}
				break;
			}
		} 
		while (childRoot <= n/2);//根不能是叶子,所以必须在最后一个有子树的节点前结束
		pointer--;
	}
}
template <class T>
void minHeap<T>::push(const T& theElement)
{
	//先插入数组末尾，然后进行起泡操作
	root[++n] = theElement;
	int pointer = n;
	while (pointer != 1)
	{
		//找到他的父亲
		int father = pointer / 2;
		if (root[father] > root[pointer])
		{
			swap(root[father], root[pointer]);
		}
		pointer = father;
	}
}
template <class T>
T minHeap<T>::pop()//把最后一个放第一个,然后下沉,因为是最后一个,所以不用比较,肯定满足条件
{
	T toReturn = root[1];//取出根元素准备返回
	T compare = root[n--];
	int pointer = 1;
	do
	{
		root[pointer] = compare;
		int lChild = pointer * 2;
		int rChild = pointer * 2 + 1;
		if (root[lChild] <= root[rChild])//左孩子更小
		{
			swap(root[lChild], root[pointer]);
			pointer = lChild;
		}
		else//右孩子更小
		{
			swap(root[rChild], root[pointer]);
			pointer = rChild;
		}
	} while (pointer < n / 2);
	return toReturn;
}
template <class T>
struct huffmanTreeNode
{
	binaryTreeNode<int>* tree;
	T weight;
};
//构造一颗哈夫曼树
template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{
	//创建一组单节点树
	huffmanTreeNode<T> *hNode = new huffmanNode<T>[n + 1];
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new binaryTreeNode<int>(i, nullptr, nullptr);
	}
	minHeap<huffmanTreeNode<T>> heap(hNode, n);
	//不断从小根堆中提取两个树合并,直到剩下一棵树
	huffmanTreeNode<T> w, x, y;
	binaryTreeNode<int> *z;
	for (i = 1; i < n; i++)
	{
		x = heap.pop();
		y = heap.pop();
		z = new binaryTreeNode<int>(0, x.tree, y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}
	return heap.top.tree;
}
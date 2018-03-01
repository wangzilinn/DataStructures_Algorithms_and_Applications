#pragma once
void testAt12();
//Ϊ�˼��ٴ��룬�������鳤�������㹻��
template<class T>
class completeBinaryTree:public binaryTree<T>//����ע��ģ�����͵ļ̳й�ϵ
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
		for (int i = n - 1; i >= 0; i--)//������������һλ,��Ϊ�ڶ��������±�0��û�õ�
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
class maxHeap:public completeBinaryTree<T>//�̳�֮ǰû��T
{
private:
	void initialize();
public:
	maxHeap(T* theRoot, int theN):completeBinaryTree<T>(theRoot, theN)
	{
		initialize();
	}
	void push(const T& theElement);
	T pop();//ɾ�����������Ԫ��
};
template <class T>
void maxHeap<T>::initialize()
{
	//�ӵ�һ���к��ӵĽڵ㿪ʼ����
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
				else//�Һ��Ӵ�������
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
			else//���һ��û���Һ���
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
	//�Ȳ�������ĩβ��Ȼ��������ݲ���
	root[++n] = theElement;
	int pointer = n;
	while (pointer != 1)
	{
		//�ҵ����ĸ���
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
	T toReturn = root[1];//ȡ����Ԫ��׼������
	T compare = root[n--];
	int pointer = 1;
	do
	{
		root[pointer] = compare;
		int lChild = pointer * 2;
		int rChild = pointer * 2 + 1;
		if (root[lChild] >= root[rChild])//���Ӹ���
		{
			swap(root[lChild], root[pointer]);
			pointer = lChild;
		}
		else//�Һ��Ӹ���
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
				else//��ߵĺ��Ӹ�С
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
		while (childRoot <= n/2);//��������Ҷ��,���Ա��������һ���������Ľڵ�ǰ����
		pointer--;
	}
}
template <class T>
void minHeap<T>::push(const T& theElement)
{
	//�Ȳ�������ĩβ��Ȼ��������ݲ���
	root[++n] = theElement;
	int pointer = n;
	while (pointer != 1)
	{
		//�ҵ����ĸ���
		int father = pointer / 2;
		if (root[father] > root[pointer])
		{
			swap(root[father], root[pointer]);
		}
		pointer = father;
	}
}
template <class T>
T minHeap<T>::pop()//�����һ���ŵ�һ��,Ȼ���³�,��Ϊ�����һ��,���Բ��ñȽ�,�϶���������
{
	T toReturn = root[1];//ȡ����Ԫ��׼������
	T compare = root[n--];
	int pointer = 1;
	do
	{
		root[pointer] = compare;
		int lChild = pointer * 2;
		int rChild = pointer * 2 + 1;
		if (root[lChild] <= root[rChild])//���Ӹ�С
		{
			swap(root[lChild], root[pointer]);
			pointer = lChild;
		}
		else//�Һ��Ӹ�С
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
//����һ�Ź�������
template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{
	//����һ�鵥�ڵ���
	huffmanTreeNode<T> *hNode = new huffmanNode<T>[n + 1];
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new binaryTreeNode<int>(i, nullptr, nullptr);
	}
	minHeap<huffmanTreeNode<T>> heap(hNode, n);
	//���ϴ�С��������ȡ�������ϲ�,ֱ��ʣ��һ����
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
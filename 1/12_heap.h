#pragma once
void testAt12();
template<class T>
class completeBinaryTree:public binaryTree<T>//����ע��ģ�����͵ļ̳й�ϵ
{
private:
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
	completeBinaryTree(T* theRoot, int theN) :root(theRoot), n(theN) { resetHeight(); }
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
	maxHeap(T* theRoot, int theN)
	{
		completeBinaryTree<T>(theRoot, theN);
		initialize();
	}
	~maxHeap()
	{
		~completeBinaryTree<T>();
	}
	void push(const T& theElement);
	T pop();//ɾ�����������Ԫ��
};
template <class T>
void maxHeap<T>::initialize()
{

}
template <class T>
void maxHeap<T>::push(const T& theElement)
{

}
template <class T>
T maxHeap<T>::pop()
{

}
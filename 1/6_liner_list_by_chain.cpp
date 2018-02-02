#include "stdafx.h"
//学习静态成员的双头链表
class DoubleLinkedList
{
private:
	DoubleLinkedList * next;
	DoubleLinkedList * prev;
	int data;
	static DoubleLinkedList * head;
public:
	DoubleLinkedList(const int& theData)
	{
		data = theData;
		if (head == nullptr)
		{
			head = this;
			prev = nullptr;
			next = nullptr;
		}
		else
		{
			head->prev = this;
			next = head;
			head = this;
			prev = nullptr;
		}
	}
	~DoubleLinkedList()//该节点的脱离过程
	{

		if (this->prev != nullptr)//如果不是头结点
			this->prev->next = this->next;
		if (this->next != nullptr)//如果不是尾节点
			this->next->prev = this->prev;
		this->next = nullptr;
		this->prev = nullptr;
	}
	void display()
	{
		DoubleLinkedList * pointer = head;
		while (pointer != nullptr)
		{
			cout << pointer->data << endl;
			pointer = pointer->next;
		}
	}
};
DoubleLinkedList* DoubleLinkedList::head = nullptr;
void testAt6()
{
	DoubleLinkedList test1(1);
	DoubleLinkedList test2(2);
	DoubleLinkedList test3(3);
	test3.display();
}
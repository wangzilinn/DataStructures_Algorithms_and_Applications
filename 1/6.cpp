#include "stdafx.h"
//ѧϰ��̬��Ա��˫ͷ����
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
	~DoubleLinkedList()//�ýڵ���������
	{

		if (this->prev != nullptr)//�������ͷ���
			this->prev->next = this->next;
		if (this->next != nullptr)//�������β�ڵ�
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
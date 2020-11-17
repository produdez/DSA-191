#include "Structure.h"
#include<iostream>
using namespace std;
stack::stack()
{
	this->Create();
}

stack::~stack()
{
	this->Clear();
}

void stack::Create()
{
	this->count = 0;
	this->top = nullptr;
}

bool stack::Push(const int& data)
{
	this->top = new node(data, top);
	this->count++;
	return true;
}

bool stack::Pop(int &dataout)
{
	if (this->count==0) return false;
	else
	{
		node* p = this->top;
		dataout = p->data;
		this->top = p->next;
		delete p;
		this->count--;
		return true;
	}
}

bool stack::Top(int& dataout)
{
	if (this->count == 0) return false;
	dataout = this->top->data;
	return true;
}

bool stack::isEmpty()
{
	return this->count == 0;
}

bool stack::isFull()
{
	return false;
}

bool stack::Clear()
{
	if (this->count != 0)
	{
		while (this->top != nullptr)
		{
			node* tmp = this->top;
			top = this->top->next;
			delete tmp;
		}
	}
	this->count = 0;
	return true;
}

int stack::Size()
{
	return this->count;
}

void stack::printStack()
{
	node* p = this->top;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

node::node()
{
	this->data = NULL;
	this->next = nullptr;
}

node::node(const int& data)
{
	this->data = data;
	this->next = NULL;
}

node::node(const int& data, node* next)
{
	this->data = data;
	this->next = next;
}

queue::queue()
{
	this->Create();
}

queue::~queue()
{
	this->Clear();
}

void queue::Create()
{
	this->count = 0;
	this->front = nullptr;
	this->rear = nullptr;
}

void queue::EnQueue(const int& data)
{
	node* newPtr = new node(data);
	if (this->count == 0)
	{
		this->front = newPtr;
	}
	else
	{
		this->rear->next = newPtr;
	}
	this->rear = newPtr;
	this->count++;
}

bool queue::DeQueue(int& dataout)
{
	if (this->count == 0) return false;
	dataout = this->front->data;
	node* p = this->front;
	if (this->count == 1)
	{
		this->rear = NULL;
	}
	this->front = this->front->next;
	this->count--;
	delete p;
	return true;
}

bool queue::QueueFront(int& dataout)
{
	if (this->count == 0) return false;
	dataout = this->front->data;
	return true;
}

bool queue::QueueRear(int& dataout)
{
	if (this->count == 0) return false;
	dataout = this->rear->data;
	return true;
}

bool queue::isEmpty()
{
	return this->count==0;
}

bool queue::isFull()
{
	return false;
}

void queue::Clear()
{
	node* tmp;
	while (this->front != NULL)
	{
		tmp = this->front;
		this->front = this->front->next;
		delete tmp;
	}
	this->front = NULL;
	this->rear = NULL;
	this->count = 0;
}

int queue::Size()
{
	return this->count;
}

void queue::printQueue()
{
	node* p = this->front;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

list::list()
{
	this->pHead = nullptr;
	this->count = 0;
}

list::~list()
{
	this->clear();
}

void list::Pushback(const int& data)
{
	if (this->pHead == nullptr)
	{
		pHead = new node(data);
		return;
	}
	node* pCur = this->pHead;
	node* pNext = pCur->next;
	while (pNext != nullptr)
	{
		pCur = pCur->next;
		pNext = pCur->next;
	}
	pCur->next = new node(data);
}

void list::clear()
{
	node* p;
	while (this->pHead)
	{
		p = this->pHead;
		this->pHead = this->pHead->next;
		delete p;
	}
	this->count = 0;
}

void list::printList()
{
	node* p = this->pHead;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

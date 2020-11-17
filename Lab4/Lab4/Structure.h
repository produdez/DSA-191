#pragma once

struct node {
	int data;
	node* next;
	node();
	node(const int& data);
	node(const int& data, node* next);
};

struct list {
	node* pHead;
	int count;
	list();
	~list();
	void Pushback(const int&);
	void clear();
	void printList();
};

struct stack {
	node* top;
	int count;
	stack();
	~stack();
	void Create();
	bool Push(const int& data);
	bool Pop(int &dataout);
	bool Top(int& dataout);
	bool isEmpty();
	bool isFull();
	bool Clear();
	int Size();
	void printStack();
};

struct queue
{
	node* front;
	node* rear;
	int count;
	queue();
	~queue();
	void Create();
	void EnQueue(const int& data);
	bool DeQueue(int& dataout);
	bool QueueFront(int& dataout);
	bool QueueRear(int& dataout);
	bool isEmpty();
	bool isFull();
	void Clear();
	int Size();
	void printQueue();
};
#include<iostream>
#include"Structure.h"
#include "Functions.h"
using namespace std;

void reverseStack(stack* st)
{
	if (st->count == 0) return;

	node* pre = nullptr;
	node* cur = st->top;
	node* next;
	while (cur)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	st->top = pre;
}

void reverseQueue(queue* que)
{
	if (que->count == 0) return;

	node* pre = nullptr;
	node* cur = que->front;
	node* next;
	while (cur)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	que->rear = que->front;
	que->front = pre;
}

void reverseListWStack(list* li)
{
	stack* sta = new stack();
	//push list into stack
	node* p = li->pHead;
	while (p)
	{
		sta->Push(p->data);
		p = p->next;
	}
	//pop stack back to list
	p = li->pHead;
	while (sta->top&& p)
	{
		sta->Pop(p->data);
		p = p->next;
	}
}

void reverseListWQueue(list* li)
{
	node* p = li->pHead;
	//use two different queue to represent a stack
	queue* q1 = new queue(); 
	queue* q2 = new queue(); // at the end, q2 holds the reversed list
	queue* swap;
	while (p)
	{
		q1->EnQueue(p->data); // push in to q1 
		int temp;
		while (q2->front != nullptr) // pop all q2 and push to q1
		{
			q2->DeQueue(temp);
			q1->EnQueue(temp);
		}
		swap = q1; // swap q2 and q1
		q1 = q2;
		q2 = swap;
		p = p->next;
	}
	//dequeue to list
	p = li->pHead;
	while (q2->front &&p)
	{
		q2->DeQueue(p->data);
		p = p->next;
	}
}

void printBinaryOfDecimal(int n)
{
	if (n == 0)
	{
		cout << 0;
		return;
	}
	stack* binary = new stack();
	while (n)
	{
		binary->Push(n % 2);
		n /= 2;
	}
	int tmp;
	while (binary->top)
	{
		binary->Pop(tmp);
		cout << tmp;

	}
}

queue* stacktoQueue(stack* sta)
{
	queue* que = new queue();
	int tmp;
	while (sta->top)
	{
		sta->Pop(tmp);
		que->EnQueue(tmp);
	}
	return que;
}

stack* queuetoStack(queue* que)
{
	stack* sta = new stack();

	node* end = que->rear;
	int tmp;
	while (que->front != end)
	{
		que->DeQueue(tmp);
		sta->Push(tmp);
		que->EnQueue(tmp);
	}
	que->DeQueue(tmp);
	sta->Push(tmp);
	que->EnQueue(tmp);
	return sta;
}


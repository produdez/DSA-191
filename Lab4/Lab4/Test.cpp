#include<iostream>
#include"Structure.h"
#include "Functions.h"
using namespace std;


int main()
{
	//create stack,queue and a list
	stack* sta = new stack();
	queue* que = new queue();
	list* lis = new list();
	// test stack ex1
	int temp;
	sta->Pop(temp);
	sta->Push(1);
	sta->Push(2);
	sta->Push(3);
	sta->Push(4);
	sta->Push(5);
	sta->Pop(temp);
	sta->printStack();
	//test queue ex2
	que->DeQueue(temp);
	que->EnQueue(6);
	que->EnQueue(7);
	que->EnQueue(8);
	que->EnQueue(9);
	que->EnQueue(10);
	que->DeQueue(temp);
	que->printQueue();
	// fill list
	lis->Pushback(11);
	lis->Pushback(12);
	lis->Pushback(13);
	lis->Pushback(14);
	lis->Pushback(15);
	lis->printList();
	//Test functions ex3
	cout << "Reversed" << endl;
	reverseStack(sta);
	sta->printStack();
	reverseQueue(que);
	que->printQueue();
	reverseListWQueue(lis);
	lis->printList();
	reverseListWStack(lis);
	lis->printList();
	//Test function ex4
	cout << "Binary convert:" << endl;
	printBinaryOfDecimal(0);
	cout << endl;
	printBinaryOfDecimal(45);
	cout << endl;
	printBinaryOfDecimal(12356);
	cout << endl;
	//Test function ex5
	cout << "Stack <-> Queue" << endl;
	stack* x = queuetoStack(que);
	x->printStack();
	queue* y = stacktoQueue(sta);
	y->printQueue();
	return 0;
}
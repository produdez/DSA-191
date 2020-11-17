#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
	LinkedList<int> link;
	for (int i = 0; i < 10; i++)
	{
		link.push_back(i);
		link.printLinkedList();
	}
	link.insert(123, 5);
	link.insert(456, 12);
	link.insert(456, 0);
	link.printLinkedList();
	//int dataOut;
	//link.remove(6,dataOut);
	//for (int i = 0; i < 5; i++)
	//	link.pop(dataOut);
	link.reverse();
	link.printLinkedList();
	return 0;
}
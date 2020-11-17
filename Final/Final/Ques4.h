#pragma once
#include <iostream>
using namespace std;

template<typename T>
struct L1Node
{
	T data =NULL;
	L1Node<T>* next = nullptr;
	L1Node() {}
	L1Node(const T&_data) :data(_data),next(nullptr) {}
	L1Node(const T& _data, L1Node<T>* _next) : data(_data), next(_next) {}
};
template<typename T>
void printLinkedList(L1Node<T>* pD)
{
	while (pD)
	{
		cout << pD->data << ' ';
		pD = pD->next;
	}
	cout << endl;
}



template<typename T>
void mergeSort(L1Node<T>*& pD, int N)
{
	printLinkedList(pD);
	if (N < 2) return;

	int lsize = N / 2;
	int rsize = N - lsize;

	L1Node<T>* pL = pD; // left list

	L1Node<T>* pTemp = pL;
	for (int i = 1; i < lsize; i++) // move one time less just to get the tail of left (which is mid)
	{
		pTemp = pTemp->next;
	}
	L1Node<T>* pR = pTemp->next; // right list is next of left list
	pTemp->next = nullptr; // disconnect left from right list


	mergeSort(pL, lsize);
	mergeSort(pR, rsize);

	//merging 
	L1Node<T>* newList = nullptr, ** pN = &newList;
	// new list is the head of the new merged list, this is unmoved
	// use pN (pointer to pointer) to do all the moving, the idea is taking the pNext of each element, starting with the pHead (which is pHead of nothing)
	// point the pNext to the element we want to merge, move the pointer of the left/right array forward, disconnect the merged element, move pN to the pNext of that element and repeat
	while (pL && pR)
	{
		if (pL->data < pR->data)
		{
			(*pN) = pL;
			pL = pL->next;
			(*pN)->next = nullptr; // since we only take one element at a time, must disconnect it 
			pN = &(*pN)->next;
		}
		else
		{
			(*pN) = pR;
			pR = pR->next;
			(*pN)->next = nullptr;
			pN = &(*pN)->next;
		}
	}

	//copy the rest
	if (pL)
	{
		(*pN) = pL; //just take all.
	}
	if (pR)
	{
		(*pN) = pR;
	}

	pD = newList;
	return;
}


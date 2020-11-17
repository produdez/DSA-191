#include <iostream>
using namespace std;


template<typename T>
struct Node
{
	T data;
	Node<T>* pNext;
	Node(T a, Node<T>* b) { this->data = a; this->pNext = b; }
};

template<typename T>
void ConcatenateOrderedList(Node<T> *&pA,Node<T> *&pB)
{
	Node<T>* pHead;
	if (pA->data < pB->data) { pHead = pA; pA = pA->pNext; }
	else { pHead = pB; pB = pB->pNext; }
	Node<T>* p = pHead;
	while (pA || pB)
	{
		if (pA == nullptr)
		{
			p->pNext = pB;
			break;
		}
		if(pB == nullptr)
		{
			p->pNext = pB;
			break;
		}
		if (pA->data > pB->data)
		{
			p->pNext = pB;
			pB = pB->pNext;
			p = p->pNext;
		}
		else
		{
			p->pNext = pA;
			pA = pA->pNext;
			p=p->pNext;
		}
	}
	pA = pHead;
	pB = nullptr;
}
int main()
{
	Node<int> *pA =new Node<int>(1, new Node<int>(5, NULL));
	Node<int> *pB = new Node<int>(1, new Node<int>(3, new Node<int>(7, NULL)));
	ConcatenateOrderedList(pA,pB);
	return 0;
}
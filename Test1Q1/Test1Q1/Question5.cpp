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
void PrintLinkedList(Node<T>* pH)
{
	Node<T>* p = pH;
	while (p)
	{
		cout << p->data << ' ';
		p = p->pNext;
	} cout << endl;
}
template<typename T>
void L1Reverse(Node<T>*& pH, int k1,int k2)
{
	Node<T>* p = pH;
	while (k1 - 2 >= 0)
	{
		p = p->pNext;
		k1--;
		k2--;
	}
	Node<T>* pEndRev = p->pNext;
	Node<T>* pPre = nullptr;
	Node<T>* pCur = p->pNext;
	Node<T>* pNext;
	while (pCur && k2)
	{
		pNext = pCur->pNext;
		pCur->pNext = pPre;
		pPre = pCur;
		pCur = pNext;
		k2--;
	}
	p->pNext = pPre;
	pEndRev->pNext = pCur;
}
int main()
{
	Node<int>* pB = new Node<int>(1, new Node<int>(3, new Node<int>(7, new Node<int>(6, new Node<int>(9, new Node<int>(0, new Node<int>(2, new Node<int>(5, NULL))))))));
	PrintLinkedList(pB);
	L1Reverse(pB, 2,5);
	PrintLinkedList(pB);
	return 0;
}
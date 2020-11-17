#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* pNext;

	Node(const T& _data) : data(_data), pNext(nullptr) {}
	Node(const T& _data,Node<T>* next) : data(_data), pNext(next) {}
};

template <typename T>
class LinkedList
{
public:
	LinkedList() {}
	~LinkedList() {}
	bool push_back(const T& data)
	{
		return this->insert(data, this->size);
	}
	bool pop(T& dataOut) {
		return remove(0, dataOut);
	}
	bool insert(const T& data, int idx) {
		if (idx < 0 || this->size < idx) return false;
		if (pHead == nullptr || idx==0) pHead = new Node<T>(data,pHead); // insert empty or insert head
		else
		{
			//insert middle or end
			Node<T>* pCur = pHead;
			Node<T>* pPre = pCur;
			while (idx>0 && pCur)
			{
				pPre = pCur;
				pCur = pCur->pNext;
				idx--;
			}
			pPre->pNext = new Node<T>(data, pCur);
		}
		this->size++;
		return true;
	}
	bool remove(int idx, T& dataOut) {
		if (this->size == 0 || idx <0 || idx >=this->size) return false;
		
		if (idx == 0)
		{
			Node<T>* p = pHead->pNext;
			delete pHead;
			pHead = p;
		}
		else
		{
			Node<T>* pCur = pHead;
			Node<T>* pPre = pCur;
			while (idx)
			{
				pPre = pCur;
				pCur = pCur->pNext;
				idx--;
			}

			Node<T>* p = pCur;
			pPre->pNext = pCur->pNext;
			dataOut = pCur->data;
			delete(p);
			this->size--;
		}
		
		return true;
	}
	void reverse()
	{
		if (this->size < 2) return;
		Node<T>* cur = pHead;
		Node<T>* pre = nullptr, *next = nullptr;
		while (cur)
		{
			next = cur->pNext;
			cur->pNext = pre;
			pre = cur;
			cur = next;
		}
		pHead = pre;
	}
	void printLinkedList()
	{
		Node<T>* pCur = this->pHead;
		while (pCur)
		{
			cout << pCur->data << ' ';
			pCur = pCur->pNext;
		}
		cout << endl;
	}
private:
	Node<T>* pHead = nullptr;
	int size = 0;
};
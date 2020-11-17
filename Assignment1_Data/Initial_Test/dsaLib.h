/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException { // use to throw exceptions, including message, and error number!!
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item { //Item of the linked list
	T data;
	L1Item<T>* pNext;
	L1Item() : pNext(NULL) {} // Null element
	L1Item(T& a) : data(a), pNext(NULL) {} // Tail only 
	L1Item(T& a, L1Item<T> *pN) : data(a), pNext(pN) {} // Data and next, for all element
};

template<typename T>
class Iterator {
	
public:
	L1Item<T>* pItem;
	Iterator() :pItem(nullptr){}
	Iterator(L1Item<T>* a) : pItem(a) {}
	~Iterator() { pItem = nullptr; }

	Iterator<T>& operator++(int) { if(pItem->pNext) pItem = pItem->pNext; return *this; } // will not move to null
	L1Item<T>& operator*() { return *pItem; } // return the data in side current element, not the element pointer
	L1Item<T>& operator->() { return *pItem; }
	/* compare operators*/
	bool operator== (const Iterator& a) { return pItem == a.pItem; }
	bool operator== (const L1Item<T>* a) { return pItem == a; }
	bool operator!= (const Iterator& a) { return pItem != a.pItem; }
	bool operator!= (const L1Item<T>* a) { return pItem != a; }
	bool atEnd() { return (pItem->pNext == nullptr); } // check if at end

};

template <class T>
class L1List {
	L1Item<T>* _pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(nullptr), _size(0) {} //default constructor, empty list
	~L1List();
	// Function that returns Iterator to a point
	Iterator<T>* iterator(int idx=0);
	/**/
	void    clean();
	bool    isEmpty() {
		return _size==0;
	}
	size_t  getSize() {
		return _size;
	}

	T& at(int i);// give the reference to the element i-th in the list
	T& operator[](int i);// give the reference to the element i-th in the list

	bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
	int		insertAfter(Iterator<T>& iCurr, T& a); // insert an element after the current iterator, 0 if success, -1 else
	int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.
	int     push_back(T& a);// insert to the end of the list
	int     insertHead(T& a);// insert to the beginning of the list

	int     removeHead();// remove the beginning element of the list
	int     removeLast();// remove the last element of the list

	void    reverse(); // reverse the list

	void    traverse(void (*op)(T&)) {
		L1Item<T>* p = _pHead;
		while (p != nullptr)
		{
			op(p->data);
			p = p->pNext;
		}
	}
	void    traverse(void (*op)(T&, void*), void* pParam) {
		L1Item<T>* p = _pHead;
		while (p != nullptr)
		{
			op(*p,pParam);
			p = p->pNext;
		}
	}
};

template<class T>
L1List<T>::~L1List()
{
	this->clean();
}

template<class T>
Iterator<T>* L1List<T>::iterator(int idx)
{
	L1Item<T>* p = _pHead;
	while (idx > 0 && p != nullptr)
	{
		p = p->pNext;
		idx--;
	}
	return new Iterator<T>(p);
}

template<class T>
void L1List<T>::clean()
{
	L1Item<T>* p = _pHead;
	while (_pHead != nullptr)
	{
		p = _pHead;
		_pHead = _pHead->pNext;
		delete p;
	}
	_size = 0;
}

template<class T>
T& L1List<T>::at(int i)
{
	L1Item<T>* p = _pHead;
	while (i > 0 && p != nullptr)
	{
		p = p->pNext;
		i--;
	}
	if (p) return p->data;
	// if out of bound
	throw new DSAException(-1, "Index out of bounds!");
}

template<class T>
T& L1List<T>::operator[](int i)
{
	L1Item<T>* p = _pHead;
	while (i > 0 && p != nullptr)
	{
		p = p->pNext;
		i--;
	}
	if (p) return p->data;
	// if out of bound
	//throw new DSAException(-1, "Index out of bounds!");
	return nullptr;
}

template<class T>
inline bool L1List<T>::find(T& a, int& idx)
{
	L1Item<T>* p = _pHead;
	idx = 0;
	while (p->data != a && p != nullptr)
	{
		p = p->pNext;
		idx++;
	}
	if (p) return true;
	//if no found
	idx = -1; return false;
}

template<class T>
int L1List<T>::insert(int idx, T& a)
{
	if (_size == 0 || _pHead == nullptr) //insert head
	{
		L1Item<T>* p = new L1Item<T>(a, _pHead);
		_pHead = p;
	}
	else if (idx <0) // i don't agree with insert index <0
	{
		return -1;
	}
	else // insert like normal, for index >= size, just push_back
	{
		L1Item<T>* pPre = _pHead, * pCur = pPre->pNext;
		while (idx > 1 && pCur != nullptr)
		{
			pPre = pCur;
			pCur = pPre->pNext;
			idx--;
		}
		pPre->pNext = new L1Item<T>(a, pCur);
	}
	_size++;
	return 0;
}
template<class T>
int L1List<T>::insertAfter(Iterator<T>& iCurr, T& a)
{
	if (_size == 0)
	{
		iCurr.pItem = new L1Item<T>(a);
		_pHead = iCurr.pItem;
	}
	else if (iCurr.pItem == nullptr)
	{
		throw new DSAException(-2, "Cant insert when current element is null!");
	}
	else 
	{
		iCurr.pItem->pNext = new L1Item<T>(a, iCurr.pItem->pNext);
	}
	_size++;
	return 0;
}
template<class T>
int L1List<T>::remove(int idx)
{
	if (idx < 0 || idx >= (int)_size || _size==0) return -1;
	if (idx == 0)
	{
		L1Item<T>* p = _pHead;
		_pHead = _pHead->pNext;
		delete p;
		_size--;
		return 0;
	}
	// else //if (idx > 0 && idx < _size)
		L1Item<T>* pPre = _pHead, * pCur = pPre->pNext;
		while (idx > 1 && pCur != nullptr)
		{
			pPre = pCur;
			pCur = pPre->pNext;
			idx--;
		}
		
		if (pCur)
		{
			pPre->pNext = pCur->pNext;
			delete pCur;
		}
		_size--;
		return 0;
}
/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T& a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
	}
	else {
		L1Item<T>* p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = new L1Item<T>(a);
	}

	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T& a) {
	L1Item<T>* p = new L1Item<T>(a,_pHead);
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}
template<class T>
void L1List<T>::reverse()
{
	if (_size < 2) return;
	L1Item<T>* pre = _pHead;
	L1Item<T>* cur = pre->pNext;
	L1Item<T>* next;

	pre->pNext = nullptr;
	while (cur != nullptr)
	{
		next = cur->pNext;
		cur->pNext = pre;
		pre = cur;
		cur = next;
	}
	_pHead = pre;
}

#endif //DSA191_A1_DSALIB_H


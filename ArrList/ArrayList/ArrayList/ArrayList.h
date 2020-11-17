#pragma once
#include "List.h"
#include <string>

template<typename T>
class ArrayList : public List<T>
{
public:
	ArrayList() :pE(nullptr), numE(0), cap(0) {}
	ArrayList(int N) : pE(new T[N]), numE(0), cap(N) {}
	~ArrayList() { delete[](pE); pE = nullptr; }

protected:
	T* pE; //pointer to our elements, essensialy our whole array
	int numE; //current number of elements
	int cap; //capacity
public:
	T& operator[](int);
	T* at(int);

	bool remove(int);
	bool insert(const T&, int);
	void resize(int);

	T* find(const T&);

	void traverse(void (*op)(T&));
	void print()
	{
		for (int i = 0; i < numE; i++)
			cout << pE[i] << ' ';
		cout << endl;
	}

	int size() { return numE; }
	bool isEmpty() { return numE == 0; }
	bool isFull() { return numE == cap; }
	void clear()
	{
		delete[] pE;
		numE = 0;
	}
};

template<typename T>
inline T& ArrayList<T>::operator[](int i)
{
	return pE[i];
}

template<typename T>
inline T* ArrayList<T>::at(int i)
{
	return &pE[i];
}

template<typename T>
inline bool ArrayList<T>::remove(int idx)
{
	if (idx < 0 || idx >= cap) return false;

	numE--;
	for (int i = idx; i < numE; i++)
		pE[i] = pE[i + 1];
	return true;
}

template<typename T>
inline bool ArrayList<T>::insert(const T& obj, int idx)
{
	if (idx<0 || idx>cap) return false;
	if (this->isFull()) this->resize(cap + 3);
	for (int i = numE - 1; i >= idx; i--)
		pE[i + 1] = pE[i];
	pE[idx] = obj;
	numE++;
	return true;
}

template<typename T>
inline void ArrayList<T>::resize(int N)
{
	T* temp = new T[N]; // new element holder
	for (int i = 0; i < N; i++)
		temp[i] = this->pE[i];

	delete[] this->pE;
	this->pE = temp;
	temp = nullptr;

	cap = N;
	if (N < numE) numE = N;
}

template<typename T>
inline T* ArrayList<T>::find(const T& obj)
{
	for (int i = 0; i < numE; i++)
	{
		if (pE[i] == obj) return &pE[i];
	}
	throw - 1;
}

template<typename T>
inline void ArrayList<T>::traverse(void(*op)(T&))
{
	for (int i = 0; i < numE; i++)
		op(pE[i]);
}

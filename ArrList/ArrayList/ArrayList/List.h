#pragma once

#include <iostream>
using namespace std;

template<typename T>
class List
{
public:
	// difference that is [] returns ref but at returns a pointer
	virtual T& operator[](int) = 0;
	virtual T* at(int) = 0;

	//remove and insert return bool to indicate successful operation
	virtual bool remove(int) = 0;
	virtual bool insert(const T&, int) = 0;

	// find returns a pointer because most of the time, when you find something, you want access and ability to change it
	virtual T* find(const T&) = 0;

	// traverse is a function that make change to all of the elements in the list, also called lamda funtion
	virtual void traverse(void (*op)(T&)) = 0;

	//Other useful functions
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;
	virtual void clear() = 0;
	virtual int size() = 0;
};
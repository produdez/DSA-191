#pragma once
#include <iostream>
using namespace std;

/* MAX HEAP*/
template <typename T>
class Heap
{
private:
	T* heap = NULL; // array head of heap heap[0] sis top
	int capacity = 0;
	int heap_size = 0;
	void reHeapUp(T*& heap,int position); // push data at position down up to correct location
	void reHeapDown(T*& heap, int position,int last_position); // push data at position down to correct location
public:
	Heap(int cap): capacity(cap) {};
	void buildHeap(T*& heap, int size); // re-arrange an array into a heap
	bool insertHeap(T*& heap, int& last, const T& data); //insert data to heap, true if done and false if full heap
	bool deleteHeap(T*& heap, int& last,  T*& dataOut); //pop the heap_top out from the heap and return it's value in dataOut
	bool checkMaxHeapValid();
	//
	int idx_parent(int position) { return (position - 1) / 2; }
	int idx_left(int position) { return position * 2 + 1; }
	int idx_right(int position) { return position * 2 + 2; }
	T getHeap() { return *heap; }
};

template<typename T>
void Heap<T>::reHeapUp(T*& heap, int position)
{
	if (position > 0) // can't heap up the top
	{
		int parent = idx_parent(position); //get parent
		if (heap[position] > heap[parent])
		{
			swap(heap[position], heap[parent]);
			reHeapUp(heap, parent);
		}
	}
}

template<typename T>
void Heap<T>::reHeapDown(T*& heap, int position, int last_position)
{
	int leftChild = position * 2 + 1;
	int rightChild = position * 2 + 2;
	if (leftChild <= last_position)
	{
		int largeChild = leftChild;
		if (rightChild <= last_position && heap[rightChild]>heap[leftChild])
		{
			largeChild = rightChild;
		}
		// the above part is to determine the larger child of the current node

		//then we check and swap if needed (recursive)
		if (heap[largeChild] > heap[position])
		{
			swap(heap[largeChild], heap[position]);
			reHeapDown(heap, largeChild, last_position);
		}
	}	
}

template<typename T>
void Heap<T>::buildHeap(T*& heap, int size)
{
	this->heap = heap;
	capacity = size;
	heap_size = size;
	//? u can do a heapUp from top of heapDOwn from end

	//this..
	//for (int i = 0; i < size; i++)
	//{
	//	//reHeapDown(heap, i,size-1);
	//	reHeapUp(heap, i);
	//}
	//or this..
	for (int i = size - 1; i >= 0; i--)
	{
		reHeapDown(heap, i, size - 1);
	}
}

template<typename T>
bool Heap<T>::insertHeap(T*& heap, int& last, const T& data)
{
	if (this->heap_size == this->capacity) return false;
	last = last + 1;
	heap[last] = data;
	reHeapUp(heap, last);
	return true;
}

template<typename T>
bool Heap<T>::deleteHeap(T*& heap,int & last, T*& dataOut)
{
	if (heap_size == 0) return false;
	*dataOut = heap[0];
	heap[0] = heap[last];
	this->heap_size--;
	reHeapDown(heap, 0, last);
}

template<typename T>
bool Heap<T>::checkMaxHeapValid()
{
	for (int i = 0; i < this->heap_size; i++)
	{
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		if (left >= heap_size || right >= heap_size) continue;
		if (heap[i] < heap[left] || heap[i] < heap[right]) return false;
	}
	return true;
}

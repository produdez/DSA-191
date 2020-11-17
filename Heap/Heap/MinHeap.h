#pragma once
#include <iostream>
using namespace std;

// MIN_HEAP
void printArr(int* arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
		cout << arr[i] << ' ';
	cout << endl;
}
void heapUp(int* heap, int idx)
{
	if (idx <= 0) return;
	int parent = (idx - 1) / 2;
	if (heap[parent] > heap[idx])
	{
		swap(heap[parent], heap[idx]);
		heapUp(heap, parent);
	}
}
void heapDown(int* heap, int idx,int heapSize)
{
	if (idx >= heapSize-1) return;
	int leftC = idx * 2 + 1;
	int rightC = idx * 2 + 2;
	int smallerC;
	if (leftC < heapSize)
	{
		smallerC = leftC;
		if (rightC < heapSize && heap[rightC] < heap[leftC])
			smallerC = rightC;

		if (heap[smallerC] < heap[idx])
		{
			swap(heap[smallerC], heap[idx]);
			heapDown(heap, smallerC, heapSize);
		}
	}
}

void buildMinHeapUp(int* arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		heapUp(arr,i);
	}
}
void buildMinHeapDown(int* arr, int arr_size)
{
	for (int i = arr_size / 2 - 1; i >= 0; i--)
	{
		heapDown(arr, i, arr_size);
	}
}
bool checkMinHeapValid(int* heap, int heap_size)
{
	for (int i = 0; i < heap_size; i++)
	{
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		if (left >= heap_size || right >= heap_size) continue;
		if (heap[i] > heap[left] || heap[i] > heap[right]) return false;
	}
	return true;
}
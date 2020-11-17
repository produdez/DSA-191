#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void heapUp(int*& heap, int pos)
{
	if (pos > 0)
	{
		int parr = (pos - 1) / 2;
		if (heap[parr] < heap[pos])
		{
			swap(heap[parr], heap[pos]);
			heapUp(heap, parr);
		}
	}
}
void reheapDown(int* & arr, int pos, int lastPos)
{
	if (pos >= lastPos) return;
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	if (left <= lastPos)
	{
		//find larger available child
		int largeChild = left;
		if (right <= lastPos && arr[right] < arr[left])
		{
			largeChild =right;
		}
		//check and swap
		if (arr[largeChild] < arr[pos])
		{
			swap(arr[pos], arr[largeChild]);
			reheapDown(arr, largeChild,lastPos);
		}
	}
}

void BuildHeap(int* arr, int N) {
	for (int i = N - 1; i >= 0; i--)
	{
		reheapDown(arr, i, N - 1);
	}
}

bool deleteHeap(int* arr, int last, int& data) {
	if (last == -1) return false;
	data = arr[0];
	arr[0] = arr[last];
	last = last - 1;
	reheapDown(arr, 0, last);
	return true;
}


void heapSortDecen(int* arr, int N)
{
	while (N>0)
	{
		BuildHeap(arr++, N--);
	}
	
}
int Kmax(int* arr, int N) {
	heapSortDecen(arr, N);
	return arr[4];
}
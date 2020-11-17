#pragma once
#include <iostream>
using namespace std;

template<typename T>
void reHeapDown(T* arr, int position, int last_position)
{
	int leftChild = position * 2 + 1;
	int rightChild = position * 2 + 2;
	if (leftChild <= last_position)
	{
		int smallChild = leftChild;
		if (rightChild <= last_position && arr[rightChild] < arr[leftChild])
		{
			smallChild = rightChild;
		}
		// the above part is to determine the smaller child of the current node

		//then we check and swap if needed (recursive)
		if (arr[smallChild] < arr[position])
		{
			swap(arr[smallChild], arr[position]);
			reHeapDown(arr, smallChild, last_position);
		}
	}
}

template<typename T>
void buildMinHeap(T* pD, int N)
{
	//start at the last non-leaf node, reheapDown and go up-ward to build min heap
	for (int i = N/2-1; i >= 0; i--)
	{
		reHeapDown(pD, i, N - 1);
	}
}

template<typename T>
bool checkMinHeap(T* pD, int N)
{
	for (int i = 0; i < N; i++)
	{
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		if (left < N && pD[left]<pD[i]) return false;
		if (right < N && pD[right]<pD[i]) return false;
	}
	return true;
}
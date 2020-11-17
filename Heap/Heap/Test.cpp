#include<iostream>
#include<chrono>
#include <random>
#include "ArrHeap.h"
#include "MinHeap.h"
using namespace std;


int test1()
{
	Heap<int> *a = new Heap<int>(0);
	int arr_size = 1000;
	int* heap = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		heap[i] = rand() % 100000;
	}
	
	auto t1 = std::chrono::high_resolution_clock::now();
	// test section
	a->buildHeap(heap, arr_size);
	// test section
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "test function took "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
		<< " nanoseconds\n";
	cout << a->checkMaxHeapValid() << endl;
	return 0;
}
int test2()
{
	int heap_size = 100000000;
	int* heap = new int[heap_size];
	for (int i = 0; i < heap_size; i++)
	{
		heap[i] = rand() % 10000;
	}
	cout << "Size: " << heap_size << endl;
	auto t1 = std::chrono::high_resolution_clock::now();
	// test section
	buildMinHeapUp(heap, heap_size);
	// test section
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "test function took "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
		<< " nanoseconds\n";
	cout << "Valid minHeap: "<<checkMinHeapValid(heap,heap_size) << endl;

	cout << endl << "SecondTest" << endl;

	t1 = std::chrono::high_resolution_clock::now();
	// test section
	buildMinHeapDown(heap, heap_size);
	// test section
	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "test function took "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
		<< " nanoseconds\n";
	cout << "Valid minHeap: " << checkMinHeapValid(heap, heap_size) << endl;
	return 0;
}
void test()
{
	int heap_size = 50;
	int* heap = new int[heap_size];
	for (int i = 0; i < heap_size; i++)
	{
		heap[i] = rand() % 10;
	}
	cout << "Size: " << heap_size << endl;

	int even = 0;
	int odd = heap_size - 1;
	while (even<odd)
	{
		while (heap[even] % 2 == 0 && even<heap_size) even++;
		while (heap[odd] % 2 == 1 && odd >= 0) odd--;
		if (even < odd)
		{
			swap(heap[even], heap[odd]);
		}
		else
		{
			break;
		}
	}
	cout << "OD:" << even << endl;
	printArr(heap, heap_size);
	for (int i = 0; i < odd + 1; i++)
	{
		buildMinHeapUp(heap+i, odd + 1-i);
	}
	for (int i = 0; i < heap_size - (odd+1);i++)
	{
		buildMinHeapUp(heap +(odd+1), heap_size - i-(odd+1));
		swap(heap[(odd + 1)], heap[heap_size - 1-i]);
	}
	printArr(heap, heap_size);
}
int main()
{
	test();
	return 0;
}
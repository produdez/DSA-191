#include <iostream>
#include <functional>
#include <random>
#include "Sorting.h"
#include "SimpleSorting.h"
using namespace std;
int oldTest()
{
	int arr[] = { 10, 13, 18, 12, 19, 9, 11, 4, 12, 2, 8, 2, 9, 6, 17, 12, 8, 10, 17, 10, 7, 16, 7, 4, 9, 16, 12, 15, 5, 3, 16, 7, 5, 4, 9, 17, 6, 7, 7, 14, 6, 20, 10, 15, 15, 10, 13, 3, 18, 11 };
	//int arr[] = { 1, 14, 16, 13, 20, 20, 13, 6, 2, 20, 7, 10, 19, 5, 9 };
	//int arr[] = { 7, 10, 9, 13, 13, 20, 20, 20, 19, 14, 16 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	function<bool(int, int)> comparator = greater<int>();
	//insert sort
	//insertSort(arr, arr_size,comparator);
	//print_arr(arr, arr_size);
	
	//shell sort
	//shellSort(arr, arr_size, comparator);
	//print_arr(arr, arr_size);

	//selection sort
	//selectionSort(arr, arr_size, comparator);
	//print_arr(arr, arr_size);

	//bubble sort
	//bubbleSort(arr, arr_size, comparator);
	//print_arr(arr, arr_size);

	//heap sort
	//heapSort(arr, arr_size, comparator);
	//print_arr(arr, arr_size);

	//merge sort
	//mergeSort(arr, arr_size, comparator);
	//print_arr(arr, arr_size);

	//quick sort
	//quickSort(arr, arr_size, comparator);
	//print_arr(arr, arr_size);
	return 0;
}
int testmergesortlinked()
{
	Node* linkedList = nullptr;
	Node** p = &linkedList;
	int list_size = 100;
	for (int i = 0; i < list_size; i++)
	{
		*p = new Node(rand() % 100);
		p = &(*p)->next;
	}
	printAllLinked(linkedList);

	mergeSortLinkedList(linkedList, list_size);
	printAllLinked(linkedList);
	return 0;
}
void testQuickSort()
{
	int arr_size = 1000;
	int* arr = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = rand() % 100;
	}
	printArr(arr, arr_size);
	system("Pause");
	quickSort(arr, arr_size);
	printArr(arr, arr_size);
}
int main()
{
	
}
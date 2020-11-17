#include <iostream>
#include"Ques1.h"
#include "Ques3.h"
#include"Ques4.h"
#include <random>
using namespace std;

void ex1();
void ex2();
void ex3();
void ex4();
template<typename T>
void print_array(T* arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		cout << arr[i] << ' ';
	}cout << endl;
}

int main()
{
	//ex1();
	//ex2();
	//ex3();
	ex4();
	return 0;
}

void ex1()
{
	int near_complete_bin_tree[] = { 10,7,12,6,8,11,13,3,6,7,9 };
	int tree_size = sizeof(near_complete_bin_tree) / sizeof(near_complete_bin_tree[0]);
	traverseLNR(near_complete_bin_tree, tree_size);
}

void ex2()
{
	cout << "Due to lack of AVL tree,... can't be tested" << endl;
}

void ex3()
{
	int arr[] = { 13, 7, 23, 12, 10, 10, 12, 14, 20, 10, 6, 1, 2, 17, 10, 29, 8, 16, 30, 5, 18, 13, 1, 16, 15, 20, 30, 1, 30, 26, 7, 26, 19, 22, 7, 29, 27, 3, 4, 21, 30, 19, 22, 28, 27, 19, 28, 28, 7, 26 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	buildMinHeap(arr, arr_size);
	print_array(arr, arr_size);
	cout << "Min heap check: " << checkMinHeap(arr, arr_size) << endl;
}

void ex4()
{
	L1Node<int>* list = new L1Node<int>(2);
	L1Node<int>* p = list;
	for (int i = 0; i < 20; i++)
	{
		p->next = new L1Node<int>(rand() % 10);
		p = p->next;
	}
	printLinkedList(list);
	mergeSort(list, 21);
	printLinkedList(list);
}

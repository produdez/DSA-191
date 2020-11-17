#pragma one
#include <iostream>
using namespace std;
void printArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << ' ';
	cout << endl;
}

#pragma region MergeSortLinkedList
struct Node
{
	int data = NULL;
	Node* next = nullptr;
	Node(int _data) { data = _data; }
};
void printAllLinked(Node* head)
{
	while (head)
	{
		cout << head->data << ' ';
		head = head->next;
	} cout << endl;
}

void mergeSortLinkedList(Node*& head, int list_size)
{
	// get left and right list
	if (list_size < 2) return;
	int n1 = list_size / 2;
	Node* pLeft = head;

	int n2 = list_size - n1;
	Node* p = head;
	for (int i = 0; i < n1 - 1; i++)
	{
		p = p->next;
	}
	Node* pRight = p->next;
	p->next = nullptr;
	////printAllLinked(pLeft);
	////printAllLinked(pRight);
	//left does not have mid value. And, need to separate left and right be setting last of left to nullptr

	//call mergeSort for each half
	mergeSortLinkedList(pLeft, n1);
	mergeSortLinkedList(pRight, n2);

	//merge them
	Node* newList = nullptr, ** ref_pNew = &newList;
	while (pLeft && pRight)
	{
		if (pLeft->data < pRight->data)
		{
			*ref_pNew = pLeft;
			pLeft = pLeft->next;
			(*ref_pNew)->next = nullptr;
			ref_pNew = &((*ref_pNew)->next);
		}
		else
		{
			*ref_pNew = pRight;
			pRight = pRight->next;
			(*ref_pNew)->next = nullptr;
			ref_pNew = &((*ref_pNew)->next);
		}
	}
	if (pLeft)
		* ref_pNew = pLeft;
	if (pRight)
		* ref_pNew = pRight;

	head = newList;
}
#pragma endregion

#pragma region QuickSort
int partition(int* arr, int arr_size)
{
	printArr(arr, arr_size);
	int mid = arr_size / 2-1;
	int head = 0;
	int tail = arr_size - 1;

	int temp = arr[mid];
	while (head<tail)
	{
		while (arr[head]<temp)
		{
			head++;
		}
		while (arr[tail]>=temp && tail>mid)
		{
			tail--;
		}
		if (head < tail)
		{
			swap(arr[head], arr[tail]);
			if (head == mid) mid = tail;
			else if (tail == mid) mid = head;
		}
		else
		{
			break;
		}
	}
	return mid;
}
void quickSort(int* arr, int arr_size)
{
	if (arr_size < 2) return;
	int mid = partition(arr, arr_size);
	quickSort(arr, mid+1);
	quickSort(arr + mid + 1, arr_size - (mid + 1));
}
#pragma endregion

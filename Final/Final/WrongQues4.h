#pragma once
#include<iostream>
using namespace std;

template<typename T>
void merge(T* arr, int left, int mid, int right)
{
	int left_size = mid - left + 1; // left array include mid val
	int right_size = right - mid; // right not include mid val
	T* L = new T[left_size];
	T* R = new T[right_size];

	int i, j, k; // walker for the left,right and merged array


	//copy from main array to left and right array
	for (i = 0; i < left_size; i++)
		L[i] = arr[left + i];
	for (j = 0; j < right_size; j++)
		R[j] = arr[mid + j + 1];

	// merging
	i = 0; //head left
	j = 0; // head right
	k = left; // head merged

	while (i < left_size && j < right_size)
	{
		if (L[i]<=R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// copy remaining
	while (i < left_size)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < right_size)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	//release
	delete[] L;
	delete[] R;
}
template<typename T>
void recur_merge_sort(T* arr, int left, int right)
{
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	recur_merge_sort(arr, left, mid);
	recur_merge_sort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}
template<typename T>
void mergeSort(T* arr, int arr_size)
{
	recur_merge_sort(arr, 0, arr_size - 1);
}

template<typename T>
void print_array(T* arr, int arr_size)
{
	for(int i=0;i<arr_size;i++)
	{
		cout << arr[i] << ' ';
	}cout << endl;
}
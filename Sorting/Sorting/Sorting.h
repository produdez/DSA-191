#pragma once
#include<iostream>
#include <functional>
using namespace std;


#pragma region PrintArray

template<typename T>
void print_arr(T* arr, int arr_size)
{
	while (arr_size > 0)
	{
		cout << *arr++ << ' ';
		arr_size--;
	}cout << endl;
}
#pragma endregion

#pragma region InsertSort
template<typename T>
void insertSort(T* arr, int arr_size,std::function<bool(T,T)> param)
{
	if (arr_size < 1) return;
	int current = 1; // assuming the first element is sorted, so we start at 1
	while (current<arr_size) 
	{
		T temp = arr[current];
		//put the current element into the right position in the sorted array
		int walker = current - 1;
		for (; walker >= 0 && param(arr[walker],temp); walker--)
		{
			arr[walker + 1] = arr[walker]; // push data back (overwrite)
		}
		arr[walker + 1] = temp; // copy current data to correct index
		current++;
	}
}
#pragma endregion

#pragma region ShellSort

template<typename T>
void SortSegment(T* arr, int arr_size, int incre_val, std::function<bool(T, T)> param) // generalized version of insert sort
{
	int current = incre_val;
	while (current < arr_size)
	{
		T temp = arr[current];
		int walker = current - incre_val;
		for (; walker >= 0 && param(arr[walker], temp); walker -= incre_val)
		{
			arr[walker + incre_val] = arr[walker];
		}
		arr[walker + incre_val] = temp;
		current += incre_val;
	}
}
int* getIncrementalValues(int n)
{
	int* incre_arr = new int[n];
	incre_arr[0] = 1;
	for (int i = 1; i < n; i++) incre_arr[i] =	incre_arr[i-1]*2+1;
	return incre_arr;
}
template <typename T>
void shellSort(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	int n = 3;
	int* incre_arr = getIncrementalValues(n);
	for (int i = n-1; i >=0; i--)
	{
		int incre_val = incre_arr[i]; // for each incremental value (from last to 1)
		print_arr(arr, arr_size); // test
		SortSegment(arr,arr_size, incre_val,param); // sort that segment
	}
}

#pragma endregion

#pragma region SeletionSort
template <typename T>
void selectionSort(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	int current = 0;
	while (current < arr_size)
	{
		T minmaxVal = arr[current];
		int minmaxIdx = current;
		for (int i = current;i<arr_size;i++)
		{
			if (!param(arr[i], minmaxVal))
			{
				minmaxVal = arr[i];
				minmaxIdx = i;
			}
		}
		swap(arr[minmaxIdx], arr[current]);
		current++;
	}
}
#pragma endregion

#pragma region BubbleSort
template<typename T>
void bubbleSort(T* arr, int arr_size, std::function<bool(int, int)> param)
{
	for (int i = 0; i < arr_size-1; i++)
	{
		for (int j = 0; j < arr_size - i - 1; j++)
		{
			if(param(arr[j],arr[j+1])) swap(arr[j],arr[j+1]);
		}
	}
}
#pragma endregion

#pragma region HeapSort
template<typename T>
void reHeapDown(T* arr,int idx, int arr_size, std::function<bool(T, T)> param)
{
	if (idx >= arr_size-1) return;
	int leftChild = idx * 2 + 1;
	int rightChild = idx * 2 + 2;
	if (leftChild < arr_size)
	{
		//getting the max/min child of the two
		int bigsmallChild = leftChild;
		if (rightChild<arr_size && param(arr[leftChild], arr[rightChild]))
		{
			bigsmallChild = rightChild;
		}

		if (param(arr[idx], arr[bigsmallChild]))
		{
			swap(arr[bigsmallChild], arr[idx]);
			reHeapDown(arr, bigsmallChild, arr_size, param);
		}
	}
}
template<typename T>
bool checkHeap(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	for (int i = 0; i < arr_size; i++)
	{
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		if (left < arr_size && param(arr[i], arr[left])) return false;
		if (right < arr_size && param(arr[i], arr[right])) return false;
	}
	return true;
}
template<typename T>
void buildHeap(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	for (int i = arr_size-1; i >=0; i--)
	{
		reHeapDown(arr,i, arr_size, param);
	}
	
}

template<typename T>
void heapSort(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	for (int i = 0; i < arr_size; i++)
	{
		buildHeap(arr + i, arr_size-i, param);
		print_arr(arr+i, arr_size-i);
		cout<<"OK?: "<<checkHeap(arr + i, arr_size - i, param)<<endl;
	}
}
#pragma endregion

#pragma region MergeSort
template<typename T>
void merge(T* arr, int left, int mid, int right, std::function<bool(T, T)> param)
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

	while (i<left_size && j < right_size)
	{
		if (param(R[j],L[i]))
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
	while (i<left_size)
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
void recur_merge_sort(T* arr, int left, int right, std::function<bool(T, T)> param)
{
	if (left >= right) return;
	print_arr(arr, right - left + 1);
	int mid = left + (right - left) / 2;
	recur_merge_sort(arr, left, mid ,param);
	recur_merge_sort(arr, mid+1, right,param);
	merge(arr, left, mid, right,param);
}
template<typename T>
void mergeSort(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	recur_merge_sort(arr, 0, arr_size - 1,param);
}
#pragma endregion

#pragma region QuickSort
int getPivot(int left, int right)
{
	return left + (right - left) / 2;
}
template <typename T>
int partition(T* arr, int left, int right, std::function<bool(T, T)> param)
{
	int pivot = getPivot(left, right);
	T temp = arr[pivot];
	while (left<=right)
	{
		//find pair of wrong placed element
		while (param(temp,arr[left]))
		{
			left++;
		}
		while (!param(temp, arr[right]) && right > pivot)
		{
			right--;
		}

		//swap them if left, right is not collided
		if (left < right)
		{
			swap(arr[left], arr[right]);
			//must update the pivot in case it is swapped
			if (left == pivot) pivot = right;
			else if (right == pivot) pivot = left;
		}
		else
		{
			break;
		}	
	}
	return pivot;
}
template<typename T>
void recur_quick_sort(T* arr, int left, int right, std::function<bool(T, T)> param)
{
	if (left >= right) return;
	int pivot =	partition(arr, left, right, param);
	recur_quick_sort(arr, left, pivot - 1,param);
	recur_quick_sort(arr, pivot + 1, right,param);
}
template <typename T>
void quickSort(T* arr, int arr_size, std::function<bool(T, T)> param)
{
	recur_quick_sort(arr, 0, arr_size - 1, param);
}
#pragma endregion

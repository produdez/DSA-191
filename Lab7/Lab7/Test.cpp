#include <iostream>
#include "ex1.h"
#include "Ex2.h"
#include "ex3.h"
using namespace std;

void ex1();
void ex2();
void ex3();
void ex4();
void ex5();
void ex6();

int main()
{
	ex5();
	return 0;
}

void ex1()
{
	string n;
	cout << "int string: ";
	cin >> n;
	cout << f1(n) << endl;
}
void ex2()
{
	int n;
	cout << "int to hash: ";
	cin >> n;
	cout << hash1(n) << endl;
	cout << hash2(n) << endl;
	cout << hash3(n) << endl;
	cout << hash4(n) << endl;
}

void ex3()
{
	int arr[] = { 5,3,9,4,10 };
	int N = sizeof(arr) / sizeof(arr[0]);
	BuildHeap(arr, N);
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << ' ';
	} cout << endl;
}
void ex4()
{
	int arr[] = { 5,3,9,4,10 };
	int N = sizeof(arr) / sizeof(arr[0]);
	BuildHeap(arr, N);
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << ' ';
	} cout << endl;
	int out=NULL;
	for (int x = 0; x < 3; x++)
	{
		
		cout << "success: " << deleteHeap(arr, N - 1, out) << endl;
			cout<<" value del: " << out << endl;
		N--;
		for (int i = 0; i < N; i++)
		{
			cout << arr[i] << ' ';
		} cout << endl;
	}
}

void ex5()
{
	int arr[] = { 10, 13, 18, 12, 19, 9, 11, 4, 12, 2, 8, 2, 9, 6, 17, 12, 8, 10, 17, 10, 7, 16, 7, 4, 9, 16, 12, 15, 5, 3, 16, 7, 5, 4, 9, 17, 6, 7, 7, 14, 6, 20, 10, 15, 15, 10, 13, 3, 18, 11 };
	int N = sizeof(arr) / sizeof(arr[0]);
	heapSortDecen(arr, N);
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << ' ';
	} cout << endl;
	cout << Kmax(arr, N) << endl;
}

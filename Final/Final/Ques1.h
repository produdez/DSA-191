#pragma once
#include <iostream>
using namespace std;
void recur_traverseLNR(int* pD, int idx, int N)
{
	if (idx >= N ) return; // at last node, return

	// get left and right node
	int left = idx * 2 + 1;
	int right = idx * 2 + 2;

	//left
	if (left < N) recur_traverseLNR(pD, left, N);
	//node
	cout << pD[idx] << ' ';
	//right
	if (right < N) recur_traverseLNR(pD, right, N);
}
void traverseLNR(int* pD, int N)
{
	recur_traverseLNR(pD,0,N);
	cout << endl;
}
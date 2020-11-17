#pragma once
#include <iostream>
#include <fstream>
using namespace std;

int hash1(int key)
{
	return key % 997 + 1;
}
int hash2(int key)
{
	int d1 = key % 10;
	int d2 = (key / 100) % 10;
	int d3 = (key / 1000) % 10;
	return d1 * 100 + d2 * 10 + d3;
}
int hash3(int key)
{
	int f1 = key % 1000;
	int f2 = key / 1000 % 1000;
	int f3 = key / 1000000 % 1000;
	return (f1+f2+f3)%1000;
}
int hash4(int key)
{
	long long int ret = ((long long int)(key) * 2016 + 11) % 997 + 1;
	return ret;
}
#pragma once
#include <iostream>
using namespace std;

int f1(string str)
{
	int f1 = 0;
	for (int i = 0; i < str.size(); i++)
	{
		int temp=1;
		for (int j = 0; j < i; j++)
		{
			temp = temp * (str[i]-'0');
		}
		f1 += 7 * temp;
	}
	return f1 % 7719;
}
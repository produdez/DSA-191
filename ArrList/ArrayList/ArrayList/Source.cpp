#include <iostream>
using namespace std;

#include "ArrayList.h"
int main()
{
	ArrayList<int> a(5);
	cout << a.isEmpty() << endl;
	return 0;
}
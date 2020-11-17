#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

#include "ArrayList.h"
int main()
{
	ArrayList<int> a(5);
	for (int i = 0; i < 5; i++)
	{
		a.insert(rand() % 10, i);
	}
	a.print();
	a.insert(12, 3);
	a.print();
	a.remove(0);
	a.print();
	*(a.find(7)) = 100;
	a.print();

	a.traverse([](int& a)-> void {
		});
	return 0;
}
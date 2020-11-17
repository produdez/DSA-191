#include <iostream>
using namespace std;


int CompareString(const char* str1, const char* str2)
{
	while (*str1!='\0' && *str2!='\0')
	{
		if (*str1 > * str2) return 1;
		if (*str1 < * str2) return -1;
		str1++;
		str2++;
	}
	return 0;
}
int main() {
	cout << CompareString("ab", "ab")<<endl;
	cout << CompareString("abc", "abba")<<endl;
	cout << CompareString("abcd", "abd") << endl;
	return 0;
}
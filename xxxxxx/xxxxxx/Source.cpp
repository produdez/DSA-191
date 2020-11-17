#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>  
#include <string>
using namespace std;

vector<string> split_string(string);

/*
 * Complete the twoStacks function below.
 */
int twoStacks(int x, vector<int> a, vector<int> b) {
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	int sum = 0, count = 0;
	vector<int> removeA;
	while (a.size() && sum<=x) // try to take as much from a as possible
	{
		if (sum + a.back() > x) break;
		sum += a.back();
		removeA.push_back(a.back());
		a.pop_back();
	}
	count = removeA.size();
	//check over to b, add b and remove a until there's valid state or B's empty, save the largest number count
	vector<int> removeB;
	while (b.size())
	{
		//add one B in
		sum += b.back();
		removeB.push_back(b.back());
		b.pop_back();
		
		//remove A until it's okay or no A left
		while (sum>x && !removeA.empty())
		{
			int temp = removeA.back();
			a.push_back(temp);
			sum -= temp;
			removeA.pop_back();
		}

		//if there's a new valid sum and, the count is better, update
		int newCount = removeA.size() + removeB.size();
		if (sum <= x && newCount>count)
		{
			count = newCount;
		}
	}
	return count;
}

int test2()
{
	ofstream fout;
	fout.open("out.txt");

	std::ifstream in("in.txt");
	std::streambuf* cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

	int g;
	cin >> g;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int g_itr = 0; g_itr < g; g_itr++) {
		string nmx_temp;
		getline(cin, nmx_temp);

		vector<string> nmx = split_string(nmx_temp);

		int n = stoi(nmx[0]);

		int m = stoi(nmx[1]);

		int x = stoi(nmx[2]);

		string a_temp_temp;
		getline(cin, a_temp_temp);

		vector<string> a_temp = split_string(a_temp_temp);

		vector<int> a(n);

		for (int a_itr = 0; a_itr < n; a_itr++) {
			int a_item = stoi(a_temp[a_itr]);

			a[a_itr] = a_item;
		}

		string b_temp_temp;
		getline(cin, b_temp_temp);

		vector<string> b_temp = split_string(b_temp_temp);

		vector<int> b(m);

		for (int b_itr = 0; b_itr < m; b_itr++) {
			int b_item = stoi(b_temp[b_itr]);

			b[b_itr] = b_item;
		}

		int result = twoStacks(x, a, b);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
		return x == y and x == ' ';
		});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}

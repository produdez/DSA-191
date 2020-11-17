#include<iostream>
#include <sstream>
using namespace std;

// ..............Define structure part..............................
struct node {
	string data;
	node* next;
	node();
	node(const string& data);
	node(const string& data, node* next);
};

struct stack {
	node* top;
	int count;
	stack();
	~stack();
	void Create();
	bool Push(const string& data);
	bool Pop(string& dataout);
	bool Top(string& dataout);
	bool isEmpty();
	bool isFull();
	bool Clear();
	int Size();
	void printStack();
};
using namespace std;
stack::stack()
{
	this->Create();
}

stack::~stack()
{
	this->Clear();
}

void stack::Create()
{
	this->count = 0;
	this->top = nullptr;
}

bool stack::Push(const string& data)
{
	this->top = new node(data, top);
	this->count++;
	return true;
}

bool stack::Pop(string& dataout)
{
	if (this->count == 0) return false;
	else
	{
		node* p = this->top;
		dataout = p->data;
		this->top = p->next;
		delete p;
		this->count--;
		return true;
	}
}

bool stack::Top(string& dataout)
{
	if (this->count == 0) return false;
	dataout = this->top->data;
	return true;
}

bool stack::isEmpty()
{
	return this->count == 0;
}

bool stack::isFull()
{
	return false;
}

bool stack::Clear()
{
	if (this->count != 0)
	{
		while (this->top != nullptr)
		{
			node* tmp = this->top;
			top = this->top->next;
			delete tmp;
		}
	}
	this->count = 0;
	return true;
}

int stack::Size()
{
	return this->count;
}

void stack::printStack()
{
	node* p = this->top;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

node::node()
{
	this->data = nullptr;
	this->next = nullptr;
}

node::node(const string& data)
{
	this->data = data;
	this->next = NULL;
}

node::node(const string& data, node* next)
{
	this->data = data;
	this->next = next;
}
// ..............Define structure part..............................


//..... Main functions.....
bool isNumber(const string& s);
string calculateStringNum(string opr, string int1, string int2);


int EvaluatePostfix(const char* p)
{
	//char* p = a;
	stack* stk = new stack();
	stringstream ss(p);
	string temp;
	string num1;
	string num2;
	while (!ss.eof())
	{
		ss >> temp;
		if (isNumber(temp)) stk->Push(temp);
		else
		{
			stk->Pop(num1);
			stk->Pop(num2);
			stk->Push(calculateStringNum(temp, num2, num1));
		}
	}
	
	//pop the last element as the answer
	stk->Pop(num1);
	return stoi(num1);
}
bool isNumber(const string &s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
string calculateStringNum(string opr, string int1, string int2)
{
	int ans;
	if (opr == "+")
	{
		ans = stoi(int1) + stoi(int2);
		return to_string(ans);
	}
	if (opr == "-")
	{
		ans = stoi(int1) - stoi(int2);
		return to_string(ans);
	}
	if (opr == "*")
	{
		ans = stoi(int1) * stoi(int2);
		return to_string(ans);
	}
	if (opr == "/")
	{
		ans = stoi(int1) / stoi(int2);
		return to_string(ans);
	}
}

int main()
{	
	cout << EvaluatePostfix("6 12 +")<<endl;
	cout << EvaluatePostfix("6 2 + 5 *")<<endl;
	cout << EvaluatePostfix("6 2 /") << endl;
	cout << EvaluatePostfix("6 2 -") << endl;
	cout << EvaluatePostfix("6 2 - 5 6 * +")<<endl;
	return 0;
}
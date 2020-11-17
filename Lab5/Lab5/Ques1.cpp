#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

class Node
{
public:
	int data=NULL;
	Node* left = NULL;
	Node* right = NULL;

};

class BinaryTree
{
private:
	Node* root = NULL;

	bool insert(Node*& root, int value) {
		if (root == NULL) {
			root = new Node();
			root->data = value;
			return true;
		}
		else if (root->data > value) {
			return insert(root->left, value);
		}
		else return insert(root->right, value);
	}

	// TODO: Add any needed member functions here
	bool findFrom(int value, Node* top)
	{
		if (top->data == value) return true;
		if (top->left == NULL && top->right == NULL) return false;
		bool found=false;
		if (top->left) found = findFrom(value, top->left);
		if (found) return found;
		if (top->right) found = findFrom(value, top->right);
		return found;
	}
	bool find_n_stack(int value,Node* top,stack<int>& stk)
	{
		if (top->data == value)
		{
			stk.push(top->data);
			return true;
		}
		if (top->left == NULL && top->right == NULL) return false;
		bool found = false;
		if (top->left) found = find_n_stack(value, top->left,stk);
		if (found)
		{
			stk.push(top->data);
			return found;
		}
		if (top->right) found = find_n_stack(value, top->right,stk);
		if (found)
		{
			stk.push(top->data);
			return found;
		}
	}
	void print(Node* root)
	{
		if (root != NULL)
		{
			cout << root->data << " ";
			print(root->left);
			print(root->right);
		}
	}
	Node* find_n_point(int value,Node* top)
	{
		if (top->data == value) return top;
		if (top->left == NULL && top->right == NULL) return NULL;
		Node* pFound = NULL;
		if (top->left) pFound = find_n_point(value, top->left);
		if (pFound) return pFound;
		if (top->right) pFound = find_n_point(value, top->right);
		return pFound;
	}
	void searchNode(int value, Node* curr, Node* parr)
	{
		while (curr != NULL && curr->data!=value)
		{
			parr = curr;
			if (value < curr->data)
				curr = curr->left;
			else
				curr = curr->right;
		}
	}
	bool remove(Node* top)
	{
		if (top->left == NULL && top->right == NULL) {
			if (top == this->root)
			{
				this->root = NULL;
			}
			Node* del = top;
			top = NULL;
			delete del; 
			return true; 
		} //if leaf delete and return true
		
		Node* p = top->right; // if has right sub, take min (left) of that
		Node* pPre = NULL;
		if(p)
		{
			while (p->left)
			{
				pPre = p;
				p = p->left;
			}
			// swap min right and top
			int temp = top->data;
			top->data = p->data;
			p->data = temp;
			//delete, caring it's right sub tree and return true
			if (pPre) pPre->left = p->right;
			else (top->right) = p->right;
			delete p;
			return true;
		}
		//if no right subtree, means has left, get max of that.
		{
			p = top->left;
			while (p->right)
			{
				pPre = p;
				p = p->right;
			}
			//swap
			int temp = top->data;
			top->data = p->data;
			p->data = temp;
			//deleting
			if (pPre) pPre->right = p->left;
			else (top->left) = p->left;
			delete p;
			return true;
		}	
	}
	bool inOrder(Node* curr)
	{	
		if (curr->left == NULL && curr->right == NULL)
		{
			cout << curr->data;
			return 1;
		}
		if(curr->left)
		if(inOrder(curr->left))
				cout << curr->data;
		if (curr->right)
			if (inOrder(curr->right) && !curr->left)
				cout << curr->data;
	}
public:

	bool insert(int value)
	{
		return insert(root, value);
	}
	void print()
	{
		print(root);
	}

	bool find(int value)
	{
		return this->findFrom(value,this->root);
	}
	void find_and_print(int value)
	{
		stack<int> pre_post;
		find_n_stack(value, this->root,pre_post);
		if (pre_post.empty())
		{
			cout << "Cannot find!" << endl << "Cannot find!";
			return;
		}
		stack<int> post_pre;
		while (!pre_post.empty())
		{
			int tmp = pre_post.top();
			post_pre.push(tmp);
			cout << tmp << ' ';
			pre_post.pop();	
		}
		cout << endl;
		while (!post_pre.empty())
		{
			cout << post_pre.top() << ' ';
			post_pre.pop();
		}
	}

	bool remove(int value)
	{
		Node* revNode = this->root;
		Node* parrNode = NULL;
		searchNode(value, revNode, parrNode);
		if (revNode == NULL) return false;
		//leaf
		if (revNode->left == NULL&& revNode->right == NULL)
		{
			//root leaf
			if (revNode == this->root)
			{
				this->root = NULL;
				delete revNode;
			}
			else
			{ //non-root leaf
				if (parrNode->left == revNode)
				{
					parrNode->left = NULL;
				}
				else
					parrNode->right = NULL;
			}	
		}
		//Non-leaf
		else if (revNode->right) //has right
		{
			Node* successor = revNode->right;
			while (successor->left)
			{
				parrNode = successor;
				successor = successor->left;
			}
			//swap
			int temp = revNode->data;
			revNode->data = successor->data;
			successor->data = temp;
			//delete
			Node* child = successor->left ? successor->left : successor->right;
			if (parrNode->left == successor)
				parrNode->left = child;
			else parrNode->right = child;
		}
		else // only left
		{
			Node* successor = revNode->left;
			while (successor->right)
			{
				parrNode = successor;
				successor = successor->right;
			}
			//swap
			int temp = revNode->data;
			revNode->data = successor->data;
			successor->data = temp;
			//delete
			Node* child = successor->left ? successor->left : successor->right;
			if (parrNode->left == successor)
				parrNode->left = child;
			else parrNode->right = child;
		}
		return true;
	}

	void insert(int* arr, int size)
	{
		for (int i = 0; i < size; i++)
		{
			this->insert(this->root, arr[i]);
		}

	}
	void inOrder()
	{
		inOrder(this->root);
	}
};

int test() {
	BinaryTree bt;
	ifstream inFile;
	int val;
	char command;
	inFile.open("Text.txt");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	while (inFile >> command) {
		switch (command)
		{
		case 'i':   // Insert value to BST
			inFile >> val;
			bt.insert(val);
			break;
		case 'r':
			inFile >> val;
			bt.remove(val);
			break;
		case 'p':
			bt.print();
			cout << endl;
			break;
		}
	}
	inFile.close();
	return 0;

}
int main() {
	BinaryTree bt;
	ifstream inFile;
	int x;
	inFile.open("Text.txt");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	int length;
	int i = 0;
	inFile >> length;
	int* arr = new int[length];
	while (inFile >> arr[i]) {
		i++;
	}
	bt.insert(arr, length);
	bt.inOrder();
}
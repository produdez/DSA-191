#include<iostream>

using namespace std;

class Node {
public:
	int data;
	Node* left;
	Node* right;
	Node(int d) {
		data = d;
		left = NULL;
		right = NULL;
	}
};

class Solution {
public:
	Node* insert(Node* root, int data) {
		if (root == NULL) {
			return new Node(data);
		}
		else {
			Node* cur;
			if (data <= root->data) {
				cur = insert(root->left, data);
				root->left = cur;
			}
			else {
				cur = insert(root->right, data);
				root->right = cur;
			}

			return root;
		}
	}

	/*
	class Node {
		public:
			int data;
			Node *left;
			Node *right;
			Node(int d) {
				data = d;
				left = NULL;
				right = NULL;
			}
	};

	*/
	void recurPrintLeft(Node* root)
	{
		if (root == nullptr) return;
		if (root->left) recurPrintLeft(root->left);
		else if (root->right) recurPrintLeft(root->right->left);
		cout << root->data << ' ';
	}
	void topView(Node* root) {
		if (root == nullptr) return;
		//print from left to root
		recurPrintLeft(root);
		//print from mid to right
		Node* pN = root->right;
		while (pN)
		{
			cout << pN->data << ' ';
			if (pN->right) pN = pN->right;
			else if (pN->left) pN = pN->left->right;
			else break;
		}
	}

}; //End of Solution

int main() {

	Solution myTree;
	Node* root = NULL;

	int t;
	int data;

	std::cin >> t;

	while (t-- > 0) {
		std::cin >> data;
		root = myTree.insert(root, data);
	}

	myTree.topView(root);
	return 0;
}

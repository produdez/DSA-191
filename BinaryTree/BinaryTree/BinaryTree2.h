#pragma once
#include <iostream>
using namespace std;


template<typename T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node() { data = NULL; left = nullptr; ; right = nullptr; }
	Node(const T& _data) { data = _data; left = nullptr; right = nullptr; }
};

template<typename T>
class BinaryTree
{
public:
	BinaryTree() { root = nullptr; }
	~BinaryTree() = default;

private:
	Node<T>* root;
	void insert(Node<T>*& root, const T& data)
	{
		if (root == nullptr) { root = new Node<T>(data); return; }

		if (data < root->data)
		{
			insert(root->left, data);
		}
		else
		{
			insert(root->right, data);
		}
	}
	Node<T>* remove(Node<T>*& root, const T& data)
	{
		if (root == nullptr) return root;
		if (data < root->data)
		{
			root->left = remove(root->left, data);
		}
		else if (data > root->data)
		{
			root->right = remove(root->right, data);
		}
		else // found
		{
			if (root->right==nullptr)
			{

				Node<T>* temp = root;
				root = root->left;
				delete temp;
				return root;
			}
			else if (root->left==nullptr)
			{
				Node<T>* temp = root;
				root = root->right;
				delete temp;
				return root;
			}
			else
			{
				Node<T>* rightChild = root->right;
				while (rightChild->left)
				{
					rightChild = rightChild->left;
				}
				root->data = rightChild->data;
				root->right = remove(root->right, rightChild->data);
			}
		}
		return root;
	}
	void printPreOrder(Node<T>* root)
	{
		if (root == nullptr) return;
		cout << root->data << ' ';
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
	void printInOrder(Node<T>* root)
	{
		if (root == nullptr) return;
		printInOrder(root->left);
		cout << root->data << ' ';
		printInOrder(root->right);
	}
	T findMin(Node<T>* root)
	{
		if (root == nullptr) return NULL;
		if ( root->left == nullptr) return root->data;
		else return findMin(root->left);
	}
	bool insertNoRep(T data, Node<T>*& root)
	{
		if (root == nullptr)
		{
			root = new Node<T>(data);
			return true;
		}

		if (data < root->data)
		{
			return insertNoRep(data, root->left);
		}
		else if (data > root->data)
		{
			return insertNoRep(data, root->right);
		}
		else
		{
			return false;
		}
	}
public:
	void insert(const T& data)
	{
		insert(root, data);
	}
	void remove(const T& data)
	{
		remove(root, data);
	}
	void printPreOrder()
	{
		printPreOrder(root);
	}
	void printInOrder()
	{
		printInOrder(root);
	}
	T findMin()
	{
		return findMin(root);
	}
	void insertIncrease(T data)
	{
		while (!insertNoRep(data, root))
			data++;
	}
	void insertTree(BinaryTree<T>* childTree)
	{
		if (childTree == nullptr) return;
		Node<T>* p = &this->root;
		while (p)
		{
			if (childTree->getHeadData() < p->data)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
	}
	T getHeadData()
	{
		return root->data;
	}
};

#include<random>

void binTree_test()
{
	BinaryTree<int>* myTreeHam = new BinaryTree<int>();
	int n = 100;
	for (int i = 0; i < n; i++)
		myTreeHam->insertIncrease(rand() & 100);
	//mytree->printPreOrder(); cout << endl;
	//for (int i = 0; i < n * 10; i++)
	//{
	//	cout << i << ": "; mytree->printPreOrder(); cout << endl;
	//	mytree->remove(rand() % 100);
	//}
		
	myTreeHam->printInOrder(); cout << endl;
	cout << "MIN: " << myTreeHam->findMin();
}
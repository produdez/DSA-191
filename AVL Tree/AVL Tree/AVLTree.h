#pragma once
#include <iostream>
using namespace std;

enum balanceFactor {LH=-1,RH=1,EH=0};

template<typename T>
struct Node
{
	T data = NULL;
	balanceFactor balance=EH;
	Node<T>* left = NULL;
	Node<T>* right = NULL;

	Node(const T& _data) { data = _data; }
};

template<typename T>
class AVLTree
{
public:
	AVLTree() = default;
	~AVLTree();
	bool insert(T data);
	bool remove(T data);
	bool find(T data);
private:
	Node<T>* root = NULL;
	void rebalanceTree();
	Node<T>* insert(Node<T>*& top, const T& data, bool& taller);
	Node<T>* leftBalance(Node<T>* top, bool& taller);
	Node<T>* rightBalance(Node<T>* top, bool& taller);
	Node<T>* rotateLeft(Node<T>*& top);
	Node<T>* rotateRight(Node<T>*& top);

};

template<typename T>
Node<T>* AVLTree<T>::insert(Node<T>*& top, const T& data, bool& taller)
{

	if (top == NULL)
	{
		top = new Node<T>(data);
		taller = true;
		return top;
	}
	if (data < top->data) //insert left
	{
		this->insert(top->left, data, taller);
		// since inserting left, chance left gets higher
		if (taller) // if something below gets taller
		{
			if (top->balance == LH) // if current is LH, means left too heavy, balance it
			{
				top = this->leftBalance(top, taller);
			}
			else if (top->balance == EH) // if EH, means now is left heavy, also higher
			{
				top->balance = LH;
			}
			else
			{
				root->balance = EH; //if RH, means now EH, no more taller
				taller = false;
			}
		}
	}
	else // insert right
	{
		this->insert(top->right, data, taller);
		// since inserting left, chance left gets higher
		if (taller) // if something below gets taller
		{
			if (top->balance == RH) // if current is RH, means left too heavy, balance it
			{
				top = this->rightBalance(top, taller);
			}
			else if (top->balance == EH) // if EH, means now is left heavy, also higher
			{
				top->balance = RH;
			}
			else
			{
				root->balance = EH; //if LH, means now EH, no more taller
				taller = false;
			}
		}
	}
}

template<typename T>
inline Node<T>* AVLTree<T>::leftBalance(Node<T>* top, bool& taller)
{
	Node<T>* leftTree = top->left;
	if (leftTree == LH) //case left left
	{
		// in case left left, only need to rotate right once and all are balanced out.
		this->rotateRight(top);
		top->balance = EH;
		top->left->balance = EH;
		taller = false;
	}
	else //case left right
	{
		Node<T>* rightTree = top->right;
		if (rightTree->balance = LH)
		{
			top->balance = RH;
			leftTree->balance = EH;
		}
		else if (rightTree->balance = EH)
		{
			leftTree->balance = EH;
		}
		else //RH
		{
			top->balance = EH;
			leftTree->balance = LH;
		}

		rightTree->balance = EH;
		top->left = this->rotateLeft(leftTree);
		top = rotateRight(top);
		taller = false;
	}

	return top;
}

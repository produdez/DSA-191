#pragma once
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>

using namespace std;

template <typename T>
class node
{
public:
	T data;
	node<T>* left = NULL;
	node<T>* right = NULL;
	int balance = 0;
	node(T data)
	{
		this->data = data;
	};
};


template <typename T>
class AVLtree
{
private:
	node<T>* root = NULL;
	
	//PRINT
	void print(node<T>*& subroot)
	{
		if (subroot == 0)
		{
			cout << '*';
			return;
		}
		cout << subroot->data;
		cout << '(';
		print(subroot->left);
		cout << '|';
		print(subroot->right);
		cout << ')';
		return;
	}
	// INSERT
	node<T>* insert(node<T>*& top, node<T>* newNode, bool& taller)
	{
		if (top == NULL)
		{
			top = newNode;
			taller = true;
			return top;
		}
		if (newNode->data < top->data) //insert left
		{
			top->left = insert(top->left, newNode, taller);
			if (taller)
			{
				if (top->balance == -1) // left
				{
					leftBalance(top, taller);
				}
				else if (top->balance == 0) //equal
				{
					top->balance = -1;
				}
				else //right
				{
					top->balance = 0;
					taller = false;
				}
			}
		}
		else //insert right
		{
			top->right = insert(top->right, newNode, taller);
			if (taller)
			{
				if (top->balance == 1) // right
				{
					rightBalance(top, taller);
				}
				else if (top->balance == 0) //equal
				{
					top->balance = 1;
				}
				else //left
				{
					top->balance = 0;
					taller = false;
				}
			}
		}
		return top;
	}
	node<T>* leftBalance(node<T>*& top, bool& taller)
	{
		node<T>* leftTree = top->left;
		if (leftTree->balance == -1) // case left left
		{
			top = rotateRight(top);
			taller = false;
			top->balance = 0;
			top->right->balance = 0;
		}
		else //case left right
		{
			node<T>* rightTree = leftTree->right;
			if (rightTree->balance == -1)
			{
				top->balance = 1;
				leftTree->balance = 0;
			}
			else if (rightTree->balance == 0)
			{
				leftTree->balance = 0;
			}
			else //RH
			{
				top->balance = 0;
				leftTree->balance = -1;
			}

			top->balance = 0;
			top->left = rotateLeft(leftTree);
			top = rotateRight(top);
			taller = false;
		}
		return top;
	}
	node<T>* rightBalance(node<T>*& top, bool& taller)
	{
		node<T>* rightTree = top->right;
		if (rightTree->balance == 1) // case right right
		{
			top = rotateLeft(top);
			top->balance = 0;
			top->left->balance = 0;
			taller = false;
		}
		else // case right left
		{
			node<T>* leftTree = rightTree->left;
			if (leftTree->balance == 1)
			{
				top->balance = -1;
				rightTree->balance = 0;
			}
			else if (leftTree->balance == 0)
			{
				rightTree->balance = 0;
			}
			else
			{
				top->balance = 0;
				rightTree->balance = 1;
			}
			top->balance = 0;
			top->right = rotateRight(rightTree);
			top = rotateLeft(top);
			taller = false;
		}
		return	top;
	}
	//ROTATE
	node<T>* rotateLeft(node<T>*& top)
	{
		node<T>* temp = top->right;
		top->right = temp->left;
		temp->left = top;
		return temp;
	}
	node<T>* rotateRight(node<T>*& top)
	{
		node<T>* temp = top->left;
		top->left = temp->right;
		temp->right = top;
		return temp;
	}
	//DELETE
	node<T>* remove(node<T>*& top, const T& del_key, bool& shorter, bool& success)
	{
		if (top == NULL) //null top situation
		{
			shorter = false;
			success = false;
			return NULL;
		}
		if (del_key < top->data) //rev left
		{
			top->left = remove(top->left, del_key, shorter, success);
			// rev left if shorter means heavy to the right
			if (shorter)
			{
				top = removeRightBalance(top, shorter);
			}
		}
		else if (del_key > top->data)//rev right
		{
			top->right = remove(top->right, del_key, shorter, success);
			// rev right if shorter means heavy to the left
			if (shorter)
			{
				top = removeLeftBalance(top, shorter);
			}
		}
		else //found key to delete
		{
			node<T>* del_node = top;
			if (del_node->right == NULL) // case no right child
			{
				node<T>* temp = top->left;
				shorter = true;
				success = true;
				delete(del_node);
				return temp;
			}
			else if (del_node->left == NULL) // case no left child
			{
				node<T>* temp = top->right;
				shorter = true;
				success = true;
				delete(del_node);
				return temp;
			}
			else //case has both left and right
			{
				//choose smallest of right
				node<T>* replace_node = top->right;
				while (replace_node->left)
				{
					replace_node = replace_node->left;
				}
				top->data = replace_node->data;
				top->right = remove(top->right, replace_node->data, shorter, success);
				if (shorter)
				{
					top = removeLeftBalance(top, shorter);
				}
			}
		}
		return top;
	}
	node<T>* removeLeftBalance(node<T>*& top, bool& shorter)
	{
		//node on the right has been removed, potential skew to left
		if (top->balance == 1) // right heavy, now equal but still shorter
		{
			top->balance = 0;
		}
		else if (top->balance == 0) // balance, now left heavy but not shorter
		{
			top->balance = -1;
			shorter = false;
		}
		else  //left heavy, now error and need fix
		{
			node<T>* leftTree = top->left;
			if (leftTree->balance == 1) // case left right
			//rotate the left sub to the left to get left left/left equals case
			{
				node<T>* rightTree = leftTree->right;
				if (rightTree->balance == 1)
				{
					leftTree->balance = -1;
					top->balance = 0;
				}
				else if (rightTree->balance == 0)
				{
					top->balance = 1;
					leftTree->balance = 0;
				}
				else
				{
					top->balance = 1;
					leftTree->balance = 0;
				}
				rightTree->balance = 0;
				top->left = rotateLeft(leftTree);
			}
			//after changing left right to ll or lq, solve them
			else
			{

			}
			if (leftTree->balance == -1) // case left left
			{
				top->balance = 0;
				leftTree->balance = 0;
			}
			else // case left equal
			{
				top->balance = -1;
				leftTree->balance = 1;
				shorter = false;
			}
			top = rotateRight(top);
		}
		return top;
	}
	node<T>* removeRightBalance(node<T>*& top, bool& shorter)
	{
		//node on the left has been removed, potential skew to right
		if (top->balance == -1) // left heavy, now equal but still shorter
		{
			top->balance = 0;
		}
		else if (top->balance == 0) // balance, now right heavy but not shorter
		{
			top->balance = 1;
			shorter = false;
		}
		else  //right heavy, now error and need fix
		{
			node<T>* rightTree = top->right;
			if (rightTree->balance == -1) // case right left
			//rotate the right sub to the right to get right right/ right equals case
			{
				node<T>* leftTree = rightTree->left;
				if (leftTree->balance == -1)
				{
					leftTree->balance = 1;
					top->balance = 0;
				}
				else if (leftTree->balance == 0)
				{
					top->balance = -1;
					leftTree->balance = 0;
				}
				else
				{
					top->balance = -1;
					rightTree->balance = 0;
				}
				leftTree->balance = 0;
				top->right = rotateRight(rightTree);
			}
			//after changing right left to rr or rq, solve them

			if (rightTree->balance == 1) // case right right
			{
				top->balance = 0;
				rightTree->balance = 0;
			}
			else // case right equal
			{
				top->balance = 1;
				rightTree->balance = -1;
				shorter = false;
			}
			top = rotateLeft(top);
		}
		return top;
	}
	//TRAVERSE
	void traverse_preOrder(node<T>* top, void f(node<T>*, void*), void* params = 0)
	{
		if (top == NULL) return;
		f(top, params);
		traverse_preOrder(top->left, f, params);
		traverse_preOrder(top->right, f, params);
	}
	void traverse_inOrder(node<T>* top, void f(node<T>*, void*), void* params = 0)
	{
		if (top == NULL) return;
		traverse_inOrder(top->left, f, params);
		f(top, params);
		traverse_inOrder(top->right, f, params);
	}
	void traverse_postOrder(node<T>* top, void f(node<T>*, void*), void* params = 0)
	{
		if (top == NULL) return;
		traverse_postOrder(top->left, f, params);
		traverse_postOrder(top->right, f, params);
		f(top, params);
	}
	//SEARCHING
	T* search_max(node<T>* subroot, bool f(node<T>*, void*), void* params = 0)
	{
		if (subroot == NULL) return NULL;
		T* found = search_max(subroot->right, f, params); // keep checking right
		if (found == NULL) // if not found yet
		{
			if (f(subroot, params) == true) return &subroot->data; // check and add
			else
			{
				found = search_max(subroot->left, f, params);
			}
		}
		return found;
	}
	T* search_min(node<T>* subroot, bool f(node<T>*, void*), void* params = 0)
	{
		if (subroot == NULL) return NULL;
		T* found = search_min(subroot->left, f, params); // keep checking left
		if (found == NULL) // if not found yet
		{
			if (f(subroot, params) == true) return &subroot->data; // check and add
			else
			{
				found = search_min(subroot->right, f, params);
			}
		}
		return found;
	}
	//COUNTING
	int countNode(node<T>* top)
	{
		if (top == NULL) return 0;
		return countNode(top->left) + countNode(top->right) + 1;
	}
	int getHeight(node<T>* top)
	{
		if (top == NULL) return -1;
		if (top->balance == -1) return 1 + getHeight(top->left);
		else return 1 + getHeight(top->right);
	} 
public:
	//CONSTRUCTOR
	AVLtree() {}
	//PUBLIC FUNCTIONS
	bool add(const T& data)
	{
		node<T>* newNode = new node<T>(data);
		bool taller = false;
		insert(this->root, newNode, taller);
		return true;
	}
	bool remove(T& data)
	{
		bool success = false;
		bool shorter = false;
		this->root = remove(this->root, data, shorter, success);
		return shorter;
	}

	void traverse_preOrder(void f(node<T>*, void*), void* params = 0)
	{
		traverse_preOrder(this->root, f, params);
	}
	void traverse_inOrder(void f(node<T>*, void*), void* params = 0)
	{
		traverse_inOrder(this->root, f, params);
	}
	void traverse_postOrder(void f(node<T>*, void*), void* params = 0)
	{
		traverse_postOrder(this->root, f, params);
	}	
	
	T* search_max(bool f(node<T>*, void*), void* params = 0)
	{
		return search_max(this->root, f, params);
	}
	T* search_min(bool f(node<T>*, void*), void* params = 0)
	{
		return search_min(this->root, f, params);
	}

	int countNode()
	{
		return countNode(this->root);
	}
	int getHeight()
	{
		return getHeight(this->root);
	}

	void print()
	{
		print(root);
	}
};
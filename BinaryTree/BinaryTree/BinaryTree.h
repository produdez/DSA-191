#pragma once
#include<iostream>
using namespace std;

template<typename T>
struct Node
{
	T data = NULL;
	Node* left = NULL;
	Node* right = NULL;
	Node(const T& _data): data(_data) {}
};

template<typename T>
class BinaryTree
{
public:
	BinaryTree() {};
	// basic operations
	void insert(const T& data);
	bool remove(const T& data);
	bool find(const T& data);
	// traversal functions
	void printInOrder();
	void printPreOrder();
	void printPostOrder();
	void printArray();
	//converting functions
	void tree_from_array(T* arr, int size);
	void tree_from_in_pre_order(T* inArr, T*& preArr, int size);
	void tree_from_in_post_order(T* inArr, T*& postArr, int size);
private:
	Node<T>* root = NULL;
	void insert(const T& data, Node<T>*& top);
	Node<T>* remove(const T& data, Node<T>*& top);
	Node<T>* findMax(Node<T>*& top);
	Node<T>* findMin(Node<T>*& top);
	Node<T>* find(const T& data, Node<T>* top);
	void printPreOrder(Node<T>* top);
	void printInOrder(Node<T>* top);
	void printPostOrder(Node<T>* top);
	void printArray(Node<T>*& top);
	void tree_from_in_revPost_order(T* inArr, T*& rev_postArr, int inSize);
};

#pragma region Functions definitions
template<typename T>
void BinaryTree<T>::insert(const T& data)
{
	insert(data, root);
}

template<typename T>
bool BinaryTree<T>::remove(const T& data)
{
	Node<T>* del_node = this->find(data, this->root);
	if (del_node == NULL) return false;
	else
		remove(data, this->root);
	return true;
}

template<typename T>
bool BinaryTree<T>::find(const T& data)
{
	return this->find(data, this->root)!=NULL;
}

template<typename T>
void BinaryTree<T>::printInOrder()
{
	printInOrder(this->root);
}

template<typename T>
void BinaryTree<T>::printPreOrder()
{
	printPreOrder(this->root);
}

template<typename T>
void BinaryTree<T>::printPostOrder()
{
	printPostOrder(this->root);
}

template<typename T>
inline void BinaryTree<T>::printArray()
{
	cout << this->root->data<<' ';
	printArray(this->root);
}

template<typename T>
void BinaryTree<T>::tree_from_array(T* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		this->insert(arr[i], this->root);
	}
}

template<typename T>
void BinaryTree<T>::tree_from_in_pre_order(T* inArr, T*& preArr, int inSize)
{
	if (inSize == 0) return;
	this->insert(*preArr,this->root); // insert the first of pre_order
	
	// find the first pre_orde in the in_order
	T* pMid = inArr;
	while (*pMid!=*preArr)
	{
		pMid++;
	}
	//split in_order into two halves
	T* leftInOrder = inArr;
	int leftSize = pMid - leftInOrder;
	T* rightInOrder = pMid + 1;
	int rightSize = inSize - leftSize - 1;
	// and construct from each halves
	tree_from_in_pre_order(leftInOrder, ++preArr, leftSize);
	tree_from_in_pre_order(rightInOrder, preArr, rightSize);
}

template<typename T>
void BinaryTree<T>::tree_from_in_post_order(T* inArr, T*& postArr, int inSize)
{
	T* rev_postArr = new T[inSize];
	T* pLast = postArr + inSize-1;
	while (pLast != (postArr - 1))
	{
		*(rev_postArr++) = *(pLast--);
	}
	rev_postArr -= inSize;
	this->tree_from_in_revPost_order(inArr, rev_postArr, inSize);
}

template<typename T>
void BinaryTree<T>::insert(const T& data, Node<T>*& top)
{
	if (top == NULL) top = new Node<T>(data);
	else if (data < top->data) insert(data, top->left);
	else insert(data, top->right);
}
template<typename T>
Node<T>* BinaryTree<T>::remove(const T& data, Node<T>*& top)
{
	if (top == NULL) return top;
	else if (data < top->data)
		top->left= remove(data, top->left);
	else if(data>top->data)
		top->right= remove(data, top->right);
	else
	{
		if (top->right==NULL)
		{
			Node<T>* temp = top->left;
			delete top;
			return temp;
		}
		else if (top->left==NULL)
		{
			Node<T>* temp = top->right;
			delete top;
			return temp;
		}
		else
		{
			Node<T>* temp = this->findMin(top);
			//swap value
			top->data = temp->data;
			//delete the min node (notice min node can only has one branch so, logic always correct and it only swap once)
			this->remove(temp->data, temp);
		}
	}

	return top;
}
template<typename T>
Node<T>* BinaryTree<T>::findMax(Node<T>*& top)
{
	if (top->right) return findMax(top->right);
	return top;
}
template<typename T>
Node<T>* BinaryTree<T>::findMin(Node<T>*& top)
{
	if (top->left) return findMin(top->left);
	return top;
}
template<typename T>
Node<T>* BinaryTree<T>::find(const T& data, Node<T>* top)
{
	if (top == NULL) return NULL;
	if (data == top->data) return top;
	if (data > top->data)
		return find(data, top->right);
	else
		return find(data, top->left);
}
template<typename T>
void BinaryTree<T>::printPreOrder(Node<T>* top)
{
	if (top == NULL) return;
	cout << top->data<<' ';
	printPreOrder(top->left);
	printPreOrder(top->right);
}
template<typename T>
void BinaryTree<T>::printInOrder(Node<T>* top)
{
	if (top == NULL) return;
	printInOrder(top->left);
	cout << top->data<<' ';
	printInOrder(top->right);
}
template<typename T>
void BinaryTree<T>::printPostOrder(Node<T>* top)
{
	if (top == NULL) return;
	printPostOrder(top->left);
	printPostOrder(top->right);
	cout << top->data<<' ';
}
template<typename T>
inline void BinaryTree<T>::printArray(Node<T>*& top)
{
	if (top == NULL) return;
	if(top->left) cout << top->left->data << ' ';
	if(top->right) cout << top->right->data << ' ';
	printArray(top->left);
	printArray(top->right);
}
template<typename T>
void BinaryTree<T>::tree_from_in_revPost_order(T* inArr, T*& rev_postArr, int inSize)
{
	if (inSize == 0) return;
	this->insert(*rev_postArr);
	T* pMid = inArr;
	while (*pMid != *rev_postArr)
	{
		pMid++;
	}
	T* leftArr = inArr;
	int leftSize = pMid - leftArr;
	T* rightArr = pMid + 1;
	int rightSize = inSize - leftSize - 1;
	tree_from_in_revPost_order(rightArr, ++rev_postArr, rightSize);
	tree_from_in_revPost_order(leftArr, rev_postArr, leftSize);
}
#pragma endregion 
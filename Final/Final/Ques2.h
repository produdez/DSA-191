#pragma one
#include <iostream>
using namespace std;

enum BalanceFactor
{
	EH = 0,
	LH = 1,
	RH = 2
};

template <typename T>
class AVLNode {
	T data;
	BalanceFactor b;
	AVLNode<T>* pLeft, * pRight;
};

template <typename T>
class AVLTree
{
public:
	AVLTree() { pRoot = nullptr; }
	int getHeight();
private:
	AVLNode<T>* pRoot;
	int getHeight(AVLNode<T>*& root);
};

template<typename T>
int AVLTree<T>::getHeight()
{
	return getHeight(this->pRoot);
}

template<typename T>
int AVLTree<T>::getHeight(AVLNode<T>*& root)
{
	if (root == NULL) return -1;
	if (root->b == RH) return 1 + getHeight(root->pRight);
	else return 1 + getHeight(root->pLeft);
}

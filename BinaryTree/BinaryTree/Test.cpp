#include <iostream>
//#include "BinaryTree.h"
#include "BinaryTree2.h"
#include<random>
using namespace std;


int oldmain()
{
	BinaryTree<int>* myTree = new BinaryTree<int>();
	for (int i=0;i<100;i++)
	{
		myTree->insert(rand()%100);
	}
	for (int i = 0; i < 100; i++)
	{
		myTree->remove(rand() % 100);
	}
	//int search;
	//cin >> search;
	//cout << myTree->find(search);
	//cout << myTree->remove(search);
	//cout << myTree->find(search);
	myTree->printPreOrder(); cout << endl;
	//myTree->printInOrder(); cout << endl;
	//myTree->printPostOrder(); cout << endl;


	//BinaryTree<int>* newTree = new BinaryTree<int>();
	//int preOrder[] = { 41 ,34, 0, 24, 67, 58, 62, 64, 69, 78 };
	//int* pre = preOrder;
	//int inOrder[] = { 0, 24, 34, 41, 58, 62, 64, 67, 69, 78 };
	//int postOrder[] = { 24, 0, 34, 64, 62, 58, 78, 69, 67, 41 };
	//int* post = postOrder;
	////newTree->tree_from_in_pre_order(inOrder, pre, 10);
	//newTree->tree_from_in_post_order(inOrder, post, 10);
	//newTree->printPostOrder(); cout << endl;
	//newTree->printInOrder();
	return 0;
}
int main()
{
	binTree_test();
	//oldmain();
	return 0;
}
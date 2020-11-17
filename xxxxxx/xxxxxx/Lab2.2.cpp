//#include <iostream>
//#include <random>
//using namespace std;
//
//
//#define LIST_SIZE 20
//
//class SinglyLinkedListNode {
//public:
//	int data;
//	SinglyLinkedListNode* next;
//
//	SinglyLinkedListNode(int node_data) {
//		this->data = node_data;
//		this->next = nullptr;
//	}
//};
//
//class SinglyLinkedList {
//public:
//	SinglyLinkedListNode* head;
//	SinglyLinkedListNode* tail;
//
//	SinglyLinkedList() {
//		this->head = nullptr;
//		this->tail = nullptr;
//	}
//
//	void insert_node(int node_data) {
//		SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);
//
//		if (!this->head) {
//			this->head = node;
//		}
//		else {
//			this->tail->next = node;
//		}
//
//		this->tail = node;
//	}
//};
//
//void print_singly_linked_list(SinglyLinkedListNode* node, string sep) {
//	while (node) {
//		cout << node->data;
//		node = node->next;
//		if (node) {
//			cout << sep;
//		}
//	}
//}
//
//void free_singly_linked_list(SinglyLinkedListNode* node) {
//	while (node) {
//		SinglyLinkedListNode* temp = node;
//		node = node->next;
//
//		free(temp);
//	}
//}
//void segregateEvenOdd(SinglyLinkedList* head_ref)
//{
//	SinglyLinkedList* newList = new SinglyLinkedList();
//	SinglyLinkedListNode* temp = head_ref->head;
//	while (temp) // insert all the even first
//	{
//		int data = temp->data;
//		if (data % 2 == 0) newList->insert_node(data);
//		temp = temp->next;
//	}
//	// then read again and insert all odds
//	temp = head_ref->head;
//	while (temp)
//	{
//		int data = temp->data;
//		if (data % 2 == 1) newList->insert_node(data);
//		temp = temp->next;
//	}
//	// delete old list
//	while (head_ref->head)
//	{
//		temp = head_ref->head;
//		head_ref->head = head_ref->head->next;
//		delete temp;
//	}
//	head_ref->head = newList->head;
//	head_ref->tail = newList->tail;
//	newList = nullptr;
//}
//
//void pairWiseSwap(SinglyLinkedList* root)
//{
//	/*
//	// 0 or 1 element, no change
//	if (root->head == nullptr || root->head->next == nullptr) return;
//
//	//Swap first pair
//	SinglyLinkedListNode* pCur = root->head;
//	SinglyLinkedListNode* pNext = pCur->next;
//	pCur->next = pNext->next;
//	pNext->next = pCur;
//	root->head = pNext;
//	if (root->tail == pNext)
//	{
//		root->tail = pCur;
//		return;
//	}
//	//Middle to end pairs
//	SinglyLinkedListNode* pPre = pCur;
//	pCur = pCur->next;
//	pNext = pCur->next;
//	while (pCur && pNext) 
//		// if Cur == null -> at end, Next == null -> no pair left
//	{
//		pCur->next = pNext->next;
//		pNext->next = pCur;
//		pPre->next = pNext;
//		pPre = pCur;
//		pCur = pCur->next;
//		if(pCur) pNext = pCur->next;
//	}
//	*/
//	if (!root->head) return;
//	
//
//	// TODO: change the algorithm to sth like the under, using two pointers and a pointer_pointer
//	SinglyLinkedListNode* pCur = root->head;
//	SinglyLinkedListNode* pNext;
//	SinglyLinkedListNode** pPre = &root->head;
//	while (pCur && pCur->next)
//	{
//		//get next one
//		pNext = pCur->next;
//		
//		//swap and fix
//		pCur->next = pNext->next;
//		pNext->next = pCur;
//		*pPre = pCur;
//
//		//move up
//		pCur = pCur->next;
//		pPre = &pCur->next;
//	}
//
//
//}
//int count(SinglyLinkedList* root, int search_for)
//{
//	int n = 0;
//	SinglyLinkedListNode* p = root->head;
//	while (p)
//	{
//		if (p->data == search_for) n++;
//		p = p->next;
//	}
//	return n;
//}
//int xx()
//{
//	SinglyLinkedList* myList = new SinglyLinkedList();
//	myList->insert_node(999);
//	for (int i = 1; i < LIST_SIZE; i++) {
//		myList->insert_node(rand() % 20);
//	}
//
//	print_singly_linked_list(myList->head, ",");
//	cout << endl;
//	//segregateEvenOdd(myList);
//	//print_singly_linked_list(myList->head, " ");
//	pairWiseSwap(myList);
//	print_singly_linked_list(myList->head, ",");
//	//cout << count(myList, 2);
//	return 0;
//}
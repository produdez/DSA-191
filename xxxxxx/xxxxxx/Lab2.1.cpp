//#include <iostream>
//#include <random>
//
//#define LIST_SIZE 10
//
//using namespace std;
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
//
//bool isPalin(SinglyLinkedListNode* head)
//{
//	if (head == nullptr || head->next == nullptr) // none to 1 elements
//		return true;
//
//	// reverse construct a new list from the given one
//	SinglyLinkedListNode* newListHead = new SinglyLinkedListNode(head->data); // pointer to the newList's head
//	SinglyLinkedListNode* pOldList = head->next; // pointer to the old list
//	while (pOldList)
//	{
//		// reverse construct (insertHead)
//		SinglyLinkedListNode* temp = new SinglyLinkedListNode(pOldList->data);
//		temp->next = newListHead;
//		newListHead = temp;
//		pOldList = pOldList->next;
//	}
//	//print test
//	print_singly_linked_list(newListHead,",");
//	//print test
//
//	//compare the old and new ones
//	SinglyLinkedListNode* pOld = head;
//	SinglyLinkedListNode* pNew = newListHead;
//	while (pOld && pNew)
//	{
//		if (pOld->data != pNew->data) return false;
//		pOld = pOld->next;
//		pNew = pNew->next;
//	}
//	return true;
//}
//
//int main()
//{
//	SinglyLinkedListNode* pHead = new SinglyLinkedListNode(999);
//	SinglyLinkedListNode* temp = pHead;
//	//
//	temp->next = new SinglyLinkedListNode(3);
//	temp = temp->next;
//	temp->next = new SinglyLinkedListNode(2);
//	temp = temp->next;
//	temp->next = new SinglyLinkedListNode(1);
//	temp = temp->next;
//	temp->next = new SinglyLinkedListNode(2);
//	temp = temp->next;
//	temp->next = new SinglyLinkedListNode(3);
//	temp = temp->next;
//	temp->next = new SinglyLinkedListNode(999);
//	temp = temp->next;
//	//
//	//for (int i = 1; i < LIST_SIZE; i++) {
//	//	SinglyLinkedListNode* new_node = new SinglyLinkedListNode(rand() % 20);
//	//	temp->next = new_node;
//	//	temp = temp->next;
//	//}
//	print_singly_linked_list(pHead,",");
//	cout << endl;
//
//
//	bool palin = isPalin(pHead);
//	cout << palin << endl;
//	return 0;
//}
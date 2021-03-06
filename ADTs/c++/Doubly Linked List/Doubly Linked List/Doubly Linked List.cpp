// Doubly Linked List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

// short way to check for no mem leaks
int numObjOnHeap = 0;

struct Node
{
	Node() {}
	Node(int data) : data(data) {}
	Node(int data, Node* prev, Node* next) : data(data), prev(prev), next(next) {}
	~Node() { cout << "Node with data: " << data << " being deleted" << endl; numObjOnHeap--; }

	int data = 0;
	Node* prev = nullptr;
	Node* next = nullptr;
};

struct BST
{
	BST() {}
	~BST()
	{
		numObjOnHeap--;
		if (size == 0) { cout << "Deleting empty BST" << endl; return; }
		cout << "Deleting BST with size: " << size << endl;
		while (head != nullptr)
		{
			Node* next = head->next;
			cout << '\t';
			delete head;
			head = next;
		}
	}

	void addFirst(int data)
	{
		Node* newNode = new Node(data);
		numObjOnHeap++;
		size++;
		// alternative would be to check sizes (size == 0)
		if (head == nullptr && tail == nullptr) { head = newNode; }
		// (size == 1)
		else if (tail == nullptr)
		{
			head->prev = newNode;
			newNode->next = head;
			tail = head;
			head = newNode;
		}
		// (size > 1)
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	}

	void addLast(int data)
	{
		Node* newNode = new Node(data);
		numObjOnHeap++;
		size++;
		//again, size can also be used for logic
		if (head == nullptr && tail == nullptr)
		{
			cout << "empty list! Node: " << newNode->data << " will be added to front of list" << endl;
			head = newNode;
		}
		else if (tail == nullptr)
		{
			head->next = newNode;
			newNode->prev = head;
			tail = newNode;
		}
		else
		{
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
	}

	void addBefore(int data, Node* existingNode)
	{
		//check for edge case where user trys to insert before the head
		if (existingNode == head) { addFirst(data); return; }
		Node* newNode = new Node(data);
		numObjOnHeap++;
		size++;

		//initializing a pointer makes it more clear what I'm doing, helps readability
		Node* oldPrev = existingNode->prev;
		oldPrev->next = newNode;
		newNode->prev = oldPrev;
		existingNode->prev = newNode;
		newNode->next = existingNode;
	}

	void addAfter(int data, Node* existingNode)
	{
		//check for edge case where user tries to insert after tail
		if (existingNode == tail || tail == nullptr) { addLast(data); return; }
		Node* newNode = new Node(data);
		numObjOnHeap++;
		size++;

		//initializing a pointer makes it more clear what I'm doing, helps readability
		Node* oldNext = existingNode->next;
		oldNext->prev = newNode;
		newNode->next = oldNext;
		existingNode->next = newNode;
		newNode->prev = existingNode;
	}

	void deleteNode(Node* nodeToBeDeleted)
	{
		size--;
		if (nodeToBeDeleted == head)
		{
			if (tail == nullptr) { head = nullptr; }
			else if (head->next == tail)
			{
				tail->prev = nullptr;
				head = tail;
				tail = nullptr;
			}
			else
			{
				head = head->next;
				head->prev = nullptr;
			}
		}
		else if (nodeToBeDeleted == tail)
		{
			if (tail->prev == head)
			{
				head->next = nullptr;
				tail = nullptr;
			}
			else
			{
				tail = tail->prev;
				tail->next = nullptr;
			}
		}
		else
		{
			Node* oldPrev = nodeToBeDeleted->prev;
			Node* oldNext = nodeToBeDeleted->next;
			oldPrev->next = oldNext;
			oldNext->prev = oldPrev;
		}
		delete nodeToBeDeleted;
	}

	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
};

ostream& operator<<(std::ostream& os, const BST* rhs)
{
	if (rhs->size == 0) { cout << "BST is empty!"; return os; }
	if (rhs->size == 1) { cout << "Bst with size: 1 has head: " << rhs->head->data << " and appears as: " << endl << '\t'; }
	else if (rhs->size > 1) { cout << "Bst with size: " << rhs->size << " has head: " << rhs->head->data << " and tail: " << rhs->tail->data << " and appears as: " << endl << '\t'; }
	Node* currNode = rhs->head;
	while (currNode != nullptr)
	{
		cout << currNode->data;
		if (currNode->next != nullptr) { cout << "<==>"; }
		currNode = currNode->next;
	}
	return os;
}


//will be creating a deep copy and deleting original objects from heap
BST* mergeTwoSortedLL(BST* firstL, BST* secL)
{
	BST* sortedBST = new BST();
	numObjOnHeap++;

	Node* l1Node = firstL->head;
	Node* l2Node = secL->head;
	if (l1Node->data < l2Node->data) 
	{ 
		sortedBST->addFirst(l1Node->data); 
		l1Node = l1Node->next; 
	}
	else 
	{ 
		sortedBST->addFirst(l2Node->data); 
		l2Node = l2Node->next;
	}

	while (l1Node != nullptr && l2Node != nullptr)
	{
		if (l1Node->data < l2Node->data)
		{
			sortedBST->addLast(l1Node->data);
			l1Node = l1Node->next;
		}
		else
		{
			sortedBST->addLast(l2Node->data);
			l2Node = l2Node->next;
		}
	}

	// add all leftovers
	if (l1Node != nullptr)
	{
		while (l1Node != nullptr)
		{
			sortedBST->addLast(l1Node->data);
			l1Node = l1Node->next;
		}
	}
	else if (l2Node != nullptr)
	{
		while (l2Node != nullptr)
		{
			sortedBST->addLast(l2Node->data);
			l2Node = l2Node->next;
		}
	}


	delete firstL;
	delete secL;
	return sortedBST;
}

bool valInLst(int data, BST* lst)
{
	cout << data << " in lst ----> ";
	Node* curr = lst->head;
	while (curr != nullptr)
	{
		if (curr->data == data) { return true; }
		else { curr = curr->next; }
	}
	return false;
}

string boolToString(bool b)
{
	if (b) { return "true"; }
	return "false";
}

int sumLL(const BST* bst)
{
	int sum = 0;
	Node* curr = bst->head;
	while (curr != nullptr)
	{
		sum += curr->data;
		curr = curr->next;
	}
	return sum;
}

//map would also be valid
long long dynam[150] = { 0, 1 };
long long fibs(int n)
{
	if (n == 0) return dynam[0];
	else if (n == 1) return dynam[1];
	else
	{
		if (dynam[n - 1] == 0) { dynam[n - 1] = fibs(n - 1); }
		else if (dynam[n - 2] == 0) { dynam[n - 2] = fibs(n - 2); }
		return dynam[n - 1] + dynam[n - 2];
	}
}



int main()
{
	cout << "======================Testing addFirst======================" << endl;
	BST* bst = new BST();
	numObjOnHeap++;
	bst->addFirst(3);
	cout << bst << endl;
	bst->addFirst(2);
	cout << bst << endl;
	bst->addFirst(1);
	cout << bst << endl;

	cout << "======================Testing addLast======================" << endl;
	BST* bstL = new BST();
	numObjOnHeap++;
	bstL->addLast(1);
	cout << bstL << endl;
	bstL->addLast(2);
	cout << bstL << endl;
	bstL->addLast(3);
	cout << bstL << endl;
	bstL->addLast(4);
	cout << bstL << endl;

	cout << "======================Testing addBefore======================" << endl;
	BST* bstAB = new BST();
	numObjOnHeap++;
	bstAB->addFirst(1);
	cout << bstAB << endl;
	bstAB->addBefore(2, bstAB->head);
	cout << bstAB << endl;
	bstAB->addBefore(3, bstAB->head->next);
	cout << bstAB << endl;

	cout << "======================Testing addAfter======================" << endl;
	BST* bstAA = new BST();
	numObjOnHeap++;
	bstAA->addFirst(1);
	cout << bstAA << endl;
	bstAA->addAfter(2, bstAA->head);
	cout << bstAA << endl;
	bstAA->addAfter(3, bstAA->tail);
	cout << bstAA << endl;

	cout << "======================Testing deleteNode======================" << endl;
	BST* bstD = new BST();
	numObjOnHeap++;
	bstD->addFirst(1);
	cout << bstD << endl;
	bstD->deleteNode(bstD->head);
	cout << bstD << endl;
	bstD->addFirst(1);
	bstD->addLast(2);
	cout << bstD << endl;
	bstD->deleteNode(bstD->head);
	cout << bstD << endl;
	bstD->addLast(3);
	bstD->addLast(4);
	cout << bstD << endl;
	bstD->deleteNode(bstD->head->next);
	cout << bstD << endl;
	bstD->addLast(5);
	bstD->addLast(6);
	cout << bstD << endl;
	bstD->deleteNode(bstD->head);
	cout << bstD << endl;

	cout << "======================Testing mergeTwoSortedLL======================" << endl;
	BST* bstFirst = new BST();
	BST* bstSec = new BST();
	numObjOnHeap += 2;
	bstFirst->addFirst(1);
	bstFirst->addLast(3);
	bstFirst->addLast(5);
	bstFirst->addLast(7);
	bstSec->addFirst(2);
	bstSec->addLast(4);
	bstSec->addLast(6);
	bstSec->addLast(8);
	cout << bstFirst << endl;
	cout << bstSec << endl;
	BST* sorted = mergeTwoSortedLL(bstFirst, bstSec);
	cout << sorted << endl;

	cout << "======================Testing valInLst======================" << endl;
	cout << boolToString(valInLst(1, sorted)) << endl;
	cout << boolToString(valInLst(3, sorted)) << endl;
	cout << boolToString(valInLst(9, sorted)) << endl;
	cout << boolToString(valInLst(8, sorted)) << endl;
	cout << boolToString(valInLst(20, sorted)) << endl;

	cout << "======================Testing sumLL======================" << endl;
	cout << sumLL(sorted) << endl;
	cout << sumLL(bst) << endl;

	cout << "======================Testing fibs(dynam allocation)======================" << endl;
	cout << "fibs(0) = " << fibs(0) << endl;
	cout << "fibs(1) = " << fibs(1) << endl;
	cout << "fibs(2) = " << fibs(2) << endl;
	cout << "fibs(3) = " << fibs(3) << endl;
	cout << "fibs(4) = " << fibs(4) << endl;
	cout << "fibs(5) = " << fibs(5) << endl;
	cout << "fibs(6) = " << fibs(6) << endl;
	cout << "fibs(15) = " << fibs(15) << endl;
	cout << "fibs(53) = " << fibs(53) << endl;
	cout << "fibs(75) = " << fibs(75) << endl;



	// when main exits, all memory will be dumped anyway
	// this section is more about me making sure my delete works correctly
	// as well as checking for any mem leaks that couldve happened in normal execution
	cout << "======================Clearing Heap======================" << endl;
	cout << "Num obj on heap before clear: " << numObjOnHeap << endl;
	delete bst;
	delete bstL;
	delete bstAB;
	delete bstAA;
	delete bstD;
	delete sorted;
	cout << "Num obj on heap after clear: " << numObjOnHeap << endl;

    return 0;
}


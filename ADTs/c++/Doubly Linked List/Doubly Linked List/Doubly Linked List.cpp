// Doubly Linked List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

struct Node
{
	Node() {}
	Node(int data) : data(data) {}
	Node(int data, Node* prev, Node* next) : data(data), prev(prev), next(next) {}
	~Node() { cout << "Node with data: " << data << " being deleted" << endl; }

	int data = 0;
	Node* prev = nullptr;
	Node* next = nullptr;
};

struct BST
{
	BST() {}
	~BST()
	{
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



int main()
{
	cout << "======================Testing addFirst======================" << endl;
	BST* bst = new BST();
	bst->addFirst(3);
	cout << bst << endl;
	bst->addFirst(2);
	cout << bst << endl;
	bst->addFirst(1);
	cout << bst << endl;

	cout << "======================Testing addLast======================" << endl;
	BST* bstL = new BST();
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
	bstAB->addFirst(1);
	cout << bstAB << endl;
	bstAB->addBefore(2, bstAB->head);
	cout << bstAB << endl;
	bstAB->addBefore(3, bstAB->head->next);
	cout << bstAB << endl;

	cout << "======================Testing addAfter======================" << endl;
	BST* bstAA = new BST();
	bstAA->addFirst(1);
	cout << bstAA << endl;
	bstAA->addAfter(2, bstAA->head);
	cout << bstAA << endl;
	bstAA->addAfter(3, bstAA->tail);
	cout << bstAA << endl;

	cout << "======================Testing deleteNode======================" << endl;
	BST* bstD = new BST();
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


	cout << "======================Clearing Heap======================" << endl;
	delete bst;
	delete bstL;
	delete bstAB;
	delete bstAA;
	delete bstD;
    return 0;
}


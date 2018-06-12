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
		while (head != nullptr)
		{
			Node* next = head->next;
			delete head;
			head = next;
		}
	}

	void addFirst(int data)
	{
		Node* newNode = new Node(data);
		size++;
		if (head == nullptr && tail == nullptr) { head = newNode; }
		else if (tail == nullptr)
		{
			head->prev = newNode;
			newNode->next = head;
			tail = head;
			head = newNode;
		}
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	}

	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
};

ostream& operator<<(std::ostream& os, const BST* rhs)
{
	Node* currNode = rhs->head;
	while (currNode != nullptr)
	{
		cout << currNode->data << ' ';
		currNode = currNode->next;
	}
	return os;
}


int main()
{
	BST* bst = new BST();
	bst->addFirst(11);
	cout << bst << endl;
	bst->addFirst(23);
	cout << bst << endl;
	bst->addFirst(14);
	cout << bst << endl;
	delete bst;
    return 0;
}


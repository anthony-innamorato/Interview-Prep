// bst.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <random>
#include <vector>
using namespace std;

struct Node
{
	Node(int data, Node* left, Node* right) : data(data), left(left), right(right) {}
	Node(int data) : data(data) {}
	Node() {}
	int data = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};

void insert(Node* root, int data)
{

}

bool valInTree(Node* root, int data)
{
	return false;
}

int bstCount(Node* root)
{
	return 0;
}

vector<int> minMax(Node* root)
{
	return { 0 };
}

int sum(Node* root)
{
	return 0;
}

int height(Node* root)
{
	return 0;
}

bool isBalance(Node* root)
{
	return false;
}

void inorder(Node* root)
{

}

void preorder(Node* root)
{

}

void postorder(Node* root)
{

}


int main()
{
	Node* a = new Node(70);
    return 0;
}


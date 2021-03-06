// C++ Misc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct ListNode
{
	int val;
	ListNode*next;
	ListNode(int x) : val(x), next(NULL) {}
};

int removeDuplicates(vector<int>& nums)
{
	if (nums.size() == 0) { return 0; }
	size_t i = 1;
	int currNum = nums[0];
	while (i < nums.size())
	{
		if (nums[i] == currNum) { i--;  nums.erase(nums.begin() + i); }
		else { currNum = nums[i];}
		i++;
	}
	return nums.size();
}

string reverseString(string s) {
	int last = s.size() - 1;
	for (size_t i = 0; i < s.size() / 2; i++)
	{
		char temp = s[i];
		s[i] = s[last];
		s[last] = temp;
		last--;
		cout << "i: " << i << " s: " << s << endl;
	}
	return s;
}

void deleteNode(ListNode* node) {
	ListNode* oldNext = node->next;
	node->val = oldNext->val; node->next = oldNext->next;
	delete oldNext;
}

bool nodeIsTail(ListNode* node)
{
	if (node->next == NULL) { return true; }
	return false;
}

ListNode* findNodeBeforeTail(ListNode* head)
{
	ListNode* copy = head;
	while (copy->next->next != NULL) { copy = copy->next; }
	return copy;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* copy = head;
	if (nodeIsTail(copy)) { delete head; return NULL; }
	if (n == 1)
	{
		copy = findNodeBeforeTail(head);
		delete copy->next;
		copy->next = NULL;
		return head;
	}
	ListNode* potTail = head;
	while (true)
	{
		for (int i = 0; i < n - 1; i++) { potTail = potTail->next; }
		cout << "for copy val: " << copy->val << " potTailVal is: " << potTail->val << endl;
		if (nodeIsTail(potTail)) { deleteNode(copy); return head; }
		copy = copy->next;
		potTail = copy;
	}
}

void printSLL(ListNode* head)
{
	cout << "Printing SLL: ";
	ListNode* copy = head;
	while (copy != NULL)
	{
		cout << copy->val;
		if (copy->next != NULL) { cout << "=>"; }
		copy = copy->next;
	}
	cout << endl;
}


int main()
{
	vector<int> nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
	cout << "length after: " << removeDuplicates(nums) << endl;
	for (const int num : nums) { cout << num << ' '; }
	cout << endl;

	vector<int> nums2 = { 1, 1, 2};
	cout << "length after: " << removeDuplicates(nums2) << endl;
	for (const int num : nums2) { cout << num << ' '; }
	cout << endl;

	cout << reverseString("hello") << endl;

	ListNode* head = new ListNode(1);
	ListNode* sec = new ListNode(2);
	head->next = sec;
	ListNode* tail = new ListNode(3);
	sec->next = tail;

	removeNthFromEnd(head, 3);
	printSLL(head);
	return 0;
}


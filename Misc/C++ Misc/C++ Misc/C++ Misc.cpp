// C++ Misc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

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
	return 0;
}


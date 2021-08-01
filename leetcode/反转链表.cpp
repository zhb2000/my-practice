#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<stack>
#include<deque>
#include<utility>
#include<cmath>
#include<cassert>
using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
	ListNode *reverseList(ListNode *head)
	{
		if (head == nullptr)
			return nullptr;
		ListNode *p = head;
		ListNode *q = head->next;
		head->next = nullptr;
		while (q != nullptr)
		{
			ListNode *qn = q->next;
			q->next = p;
			p = q; q = qn;
		}
		return p;
	}
};

int main()
{
	auto sol = new Solution();
	return 0;
}

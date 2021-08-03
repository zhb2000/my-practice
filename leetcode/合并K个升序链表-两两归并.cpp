//合并K个升序链表
//https://leetcode-cn.com/problems/merge-k-sorted-lists/
//两两归并，时间复杂度 O(knlogk)，空间复杂度 O(1)
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
	ListNode *mergeKLists(vector<ListNode *> &lists)
	{
		int k = int(lists.size());
		if (k == 0)
			return nullptr;
		for (int d = 1; d <= k; d *= 2)
		{
			for (int i = 0; i < k; i += 2 * d)
			{
				if (i + d < k)
				{
					lists[i] = merge(lists[i], lists[i + d]);
					lists[i + d] = nullptr;
				}
			}
		}
		return lists[0];
	}

	static ListNode *merge(ListNode *a, ListNode *b)
	{
		if (a == nullptr && b == nullptr)
			return nullptr;
		else if (a == nullptr)
			return b;
		else if (b == nullptr)
			return a;
		else
		{
			ListNode *head; // smaller one as head
			if (a->val < b->val)
			{
				head = a;
				a = a->next;
			}
			else
			{
				head = b;
				b = b->next;
			}
			head->next = nullptr;
			ListNode *last = head;
			while (a != nullptr && b != nullptr)
			{
				ListNode *u; //to insert
				if (a->val < b->val)
				{
					u = a;
					a = a->next;
				}
				else
				{
					u = b;
					b = b->next;
				}
				u->next = nullptr;
				last->next = u;
				last = u;
			}
			ListNode *res = (a != nullptr) ? a : b;
			while (res != nullptr)
			{
				ListNode *u = res; res = res->next;
				u->next = nullptr;
				last->next = u;
				last = u;
			}
			return head;
		}
	}
};

ListNode *make_list(const vector<int> &v)
{
	int n = int(v.size());
	if (n == 0)
		return nullptr;
	ListNode *head = new ListNode(v[0]);
	ListNode *last = head;
	for (int i = 1; i < n; i++)
	{
		ListNode *u = new ListNode(v[i]);
		u->next = nullptr;
		last->next = u;
		last = u;
	}
	return head;
}

string list2str(ListNode *head)
{
	string s;
	for (ListNode *p = head; p != nullptr; p = p->next)
	{
		s.push_back('0' + p->val);
		s.push_back(' ');
	}
	return s;
}

int main()
{
	vector<ListNode *> lists = { make_list({1,4,5}), make_list({1,3,4}), make_list({2,6}) };
	auto sol = new Solution();
	cout << list2str(sol->mergeKLists(lists)) << endl;
	return 0;
}

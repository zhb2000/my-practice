//合并K个升序链表
//https://leetcode-cn.com/problems/merge-k-sorted-lists/
//堆，时间复杂度 O(knlogk)，空间复杂度 O(logk)
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
	struct Entry
	{
		int i;
		int val;
		bool operator<(const Entry &other) const
		{
			return val > other.val;
		}
	};

	ListNode *mergeKLists(vector<ListNode *> &lists)
	{
		int k = int(lists.size());
		if (k == 0)
			return nullptr;
		priority_queue<Entry> pq;
		for (int i = 0; i < k; i++)
			if (lists[i] != nullptr)
				pq.push({ i, lists[i]->val });
		ListNode *head = nullptr, *last = nullptr;
		while (!pq.empty())
		{
			Entry entry = pq.top(); pq.pop();
			int i = entry.i;
			ListNode *u = remove_head(lists[i]);
			if (lists[i] != nullptr)
				pq.push({ i, lists[i]->val });
			if (head == nullptr)
			{
				head = u;
				last = u;
			}
			else
			{
				last->next = u;
				last = u;
			}
		}
		return head;
	}

	static ListNode *remove_head(ListNode *&head)
	{
		assert(head != nullptr);
		ListNode *u = head;
		head = u->next;
		u->next = nullptr;
		return u;
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

//排序链表
//https://leetcode-cn.com/problems/sort-list/
//归并排序（自顶向下）
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
	ListNode *sortList(ListNode *head)
	{
		return merge_sort(head, list_len(head));
	}

	static ListNode *merge_sort(ListNode *head, int len)
	{
		if (len == 0)
		{
			assert(head == nullptr);
			return nullptr;
		}
		if (len == 1)
		{
			assert(head->next == nullptr);
			return head;
		}

		int alen = len / 2;
		int blen = len - alen;
		ListNode *a, *b;
		tie(a, b) = split(head, alen);
		a = merge_sort(a, alen);
		b = merge_sort(b, blen);
		return merge(a, b);
	}

	static pair<ListNode *, ListNode *> split(ListNode *head, int alen)
	{
		if (alen == 0)
			return make_pair(nullptr, head);
		ListNode *alast = after(head, alen - 1);
		ListNode *b = alast->next;
		alast->next = nullptr;
		return make_pair(head, b);
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
			ListNode *head;
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

	static ListNode *after(ListNode *p, int step)
	{
		assert(p != nullptr);
		for (int i = 0; i < step; i++)
			p = p->next;
		return p;
	}

	static int list_len(ListNode *head)
	{
		int len = 0;
		for (ListNode *p = head; p != nullptr; p = p->next)
			len++;
		return len;
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
	ListNode *head = make_list({ 4,2,1,3 });
	auto sol = new Solution();
	head = sol->sortList(head);
	cout << list2str(head) << endl;
	return 0;
}

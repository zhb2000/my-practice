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
	bool hasCycle(ListNode *head)
	{
		if (head == nullptr)
			return false;
		ListNode *p1 = head;
		ListNode *p2 = head;
		while (true)
		{
			if (!movenxt(p2) || !movenxt(p2))
				return false;
			bool can = movenxt(p1);
			assert(can);
			if (p2 == p1)
				return true;
		}
	}

	//retrun: p is not null after move (can move)
	static bool movenxt(ListNode *&p)
	{
		assert(p != nullptr);
		p = p->next;
		return p != nullptr;
	}
};

int main()
{
	auto sol = new Solution();
	return 0;
}

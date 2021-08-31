//跳跃游戏 III
//https://leetcode-cn.com/problems/jump-game-iii/
//BFS
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
#include<numeric>
using namespace std;
template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	os << "[";
	bool isfirst = true;
	for (const auto &x : v)
	{
		if (isfirst)
			isfirst = false;
		else
			os << ", ";
		os << x;
	}
	os << "]";
	return os;
}

class Solution
{
public:
	bool canReach(vector<int> &arr, int start)
	{
		int n = int(arr.size());
		auto vis = vector<bool>(n);
		queue<int> q;
		q.push(start);
		while (!q.empty())
		{
			int i = q.front(); q.pop();
			vis[i] = true;
			if (arr[i] == 0)
				return true;
			int p = i - arr[i];
			if (0 <= p && p < n && !vis[p])
				q.push(p);
			p = i + arr[i];
			if (0 <= p && p < n && !vis[p])
				q.push(p);
		}
		return false;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> arr; int start;

	arr = { 4, 2, 3, 0, 3, 1, 2 }; start = 5;
	cout << sol->canReach(arr, start) << endl;

	arr = { 4, 2, 3, 0, 3, 1, 2 }; start = 0;
	cout << sol->canReach(arr, start) << endl;

	arr = { 3, 0, 2, 1, 2 }; start = 0;
	cout << sol->canReach(arr, start) << endl;

	return 0;
}

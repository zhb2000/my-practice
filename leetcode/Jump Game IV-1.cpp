//Jump Game IV
//https://leetcode-cn.com/problems/jump-game-iv/
//BFS，预处理：连续相同数字只保留两个
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
	struct Entry
	{
		int pos;
		int dist;
	};

	vector<int> preprocess(const vector<int> &arr)
	{
		int n = int(arr.size());
		vector<int> ret;
		ret.push_back(arr[0]);
		int same_cnt = 1;
		for (int i = 1; i < n; i++)
		{
			if (arr[i] == arr[i - 1])
				same_cnt++;
			else
				same_cnt = 0;
			if (same_cnt <= 2)
				ret.push_back(arr[i]);
		}
		return ret;
	}

	int minJumps(vector<int> &arr)
	{
		arr = preprocess(arr);
		int n = int(arr.size());
		unordered_map<int, vector<int>> num_poses;
		auto vis = vector<bool>(n);
		for (int i = 0; i < n; i++)
		{
			if (num_poses.count(arr[i]) == 0)
				num_poses[arr[i]] = {};
			num_poses[arr[i]].push_back(i);
		}
		queue<Entry> q;
		q.push({ 0, 0 });
		while (!q.empty())
		{
			Entry entry = q.front(); q.pop();
			int i = entry.pos; int dist = entry.dist;
			if (vis[i])
				continue;
			vis[i] = true;
			if (i == n - 1)
				return dist;
			if (i - 1 >= 0 && !vis[i - 1])
			{
				if (i - 1 == n - 1)
					return dist + 1;
				q.push({ i - 1, dist + 1 });
			}
			if (i + 1 < n && !vis[i + 1])
			{
				if (i + 1 == n - 1)
					return dist + 1;
				q.push({ i + 1, dist + 1 });
			}
			if (num_poses.count(arr[i]) > 0)
			{
				for (int j : num_poses[arr[i]])
				{
					if (!vis[j])
					{
						if (j == n - 1)
							return dist + 1;
						q.push({ j, dist + 1 });
					}
				}
			}
		}
		return -1;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> arr;

	arr = { 100,-23,-23,404,100,23,23,23,3,404 };
	cout << sol->minJumps(arr) << endl;

	arr = { 7 };
	cout << sol->minJumps(arr) << endl;

	arr = { 7,6,9,6,9,6,9,7 };
	cout << sol->minJumps(arr) << endl;

	arr = { 6,1,9 };
	cout << sol->minJumps(arr) << endl;

	arr = { 11,22,7,7,7,7,7,7,7,22,13 };
	cout << sol->minJumps(arr) << endl;

	arr = { 7,7,7,7,7,7,7,7,7,7,7,7,11 };
	cout << sol->minJumps(arr) << endl;

	arr = { 11,7,7,7,7,7,7,7,7,7,7,7,7 };
	cout << sol->minJumps(arr) << endl;

	return 0;
}

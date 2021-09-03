//Jump Game IV
//https://leetcode-cn.com/problems/jump-game-iv/
//BFS，保证每个节点只入队一次，保证相同值的节点只遍历一次
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

	int minJumps(vector<int> &arr)
	{
		int n = int(arr.size());
		unordered_map<int, vector<int>> num_poses;
		auto vis = vector<bool>(n); //节点是否曾入队
		unordered_set<int> num_vis; //值为 num 的节点是否曾入队
		for (int i = 0; i < n; i++)
		{
			if (num_poses.count(arr[i]) == 0)
				num_poses[arr[i]] = {};
			num_poses[arr[i]].push_back(i);
		}
		queue<Entry> q;
		q.push({ 0, 0 });
		vis[0] = true;
		while (!q.empty())
		{
			Entry entry = q.front(); q.pop();
			int i = entry.pos; int dist = entry.dist;
			if (i == n - 1)
				return dist;
			if (i - 1 >= 0 && !vis[i - 1])
			{
				q.push({ i - 1, dist + 1 });
				vis[i - 1] = true;
			}
			if (i + 1 < n && !vis[i + 1])
			{
				q.push({ i + 1, dist + 1 });
				vis[i + 1] = true;
			}
			if (num_vis.count(arr[i]) == 0) //保证相同值的节点只被遍历一次
			{
				for (int j : num_poses[arr[i]])
				{
					if (!vis[j])
					{
						q.push({ j, dist + 1 });
						vis[j] = true;
					}
				}
				num_vis.insert(arr[i]);
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


//两球之间的磁力
//https://leetcode-cn.com/problems/magnetic-force-between-two-balls/
//二分答案
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
	int min_diff(const vector<int> &position)
	{
		int ans = int(1e9);
		int n = int(position.size());
		for (int i = 1; i < n; i++)
			ans = min(ans, position[i] - position[i - 1]);
		return ans;
	}

	bool available(const vector<int> &position, int m, int x)
	{
		int n = int(position.size());
		int cnt = 1;
		int diff_sum = 0;
		for (int i = 1; i < n; i++)
		{
			int diff = position[i] - position[i - 1];
			diff_sum += diff;
			if (diff_sum >= x)
			{
				cnt++;
				diff_sum = 0;
			}
		}
		return cnt >= m;
	}

	int maxDistance(vector<int> &position, int m)
	{
		sort(position.begin(), position.end());
		int n = int(position.size());
		int l = min_diff(position);
		int r = position[n - 1] - position[0] + 1;
		while (l < r)
		{
			int mid = (l + r) / 2;
			if (available(position, m, mid))
				l = mid + 1;
			else
				r = mid;
		}
		return l - 1;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> position; int m;
	
	position = { 1, 2, 3, 4, 7 }; m = 3;
	cout << sol->maxDistance(position, m) << endl;

	position = { 5, 4, 3, 2, 1, 1000000000 }; m = 2;
	cout << sol->maxDistance(position, m) << endl;

	return 0;
}

//Jump Game
//https://leetcode-cn.com/problems/jump-game/
//贪心
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
	bool canJump(vector<int> &nums)
	{
		int n = int(nums.size());
		int bound = 0;
		int nxt_bound = 0;
		for (int i = 0; i < n; i++)
		{
			if (i > nxt_bound)
				break;
			else if (i == bound)
			{
				bound = nxt_bound;
			}
			nxt_bound = max(nxt_bound, i + nums[i]);
			if (nxt_bound >= n - 1)
				break;
		}
		return nxt_bound >= n - 1;
	}
};

int main()
{
	auto sol = new Solution();

	return 0;
}

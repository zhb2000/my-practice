//跳跃游戏 II
//https://leetcode-cn.com/problems/jump-game-ii/
//DP，时间复杂度 O(n^2)，空间复杂度 O(n)
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
	int jump(vector<int> &nums)
	{
		int n = int(nums.size());
		auto f = vector<int>(n);
		f[n - 1] = 0;
		for (int i = n - 2; i >= 0; i--)
		{
			int ans = int(1e9);
			for (int step = 1; step <= nums[i] && i + step < n; step++)
				ans = min(ans, 1 + f[i + step]);
			f[i] = ans;
		}
		//cout << f << endl;
		return f[0];
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> nums = { 2,3,1,1,4 };
	cout << sol->jump(nums) << endl;
	nums = { 2,3,0,1,4 };
	cout << sol->jump(nums) << endl;
	return 0;
}

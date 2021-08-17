//跳跃游戏 II
//https://leetcode-cn.com/problems/jump-game-ii/
//贪心，时间复杂度 O(n)，空间复杂度 O(1)
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
		//跳 step 步最远能跳到 end
		int step = 0;
		int end = 0;
		int max_pos = 0;
		for (int i = 0; i < n - 1; i++)
		{
			max_pos = max(max_pos, i + nums[i]);
			if (i == end)
			{
				//现在知道跳 n-1 步最远能跳到 max_pos
				step += 1;
				end = max_pos;
				if (end >= n - 1)
					break;
			}
		}
		return step;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> nums;
	nums = { 2,3,1,1,4 };
	cout << sol->jump(nums) << endl;
	nums = { 2,3,0,1,4 };
	cout << sol->jump(nums) << endl;
	nums = { 2,3,1 };
	cout << sol->jump(nums) << endl;
	nums = { 7,0,9,6,9,6,1,7,9,0,1,2,9,0,3 };
	cout << sol->jump(nums) << endl;
	return 0;
}

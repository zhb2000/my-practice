//乘积为正数的最长子数组长度
//https://leetcode-cn.com/problems/maximum-length-of-subarray-with-positive-product/
//DP
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

using namespace std;

class Solution
{
public:
	vector<int> pos;
	vector<int> neg;

	int getMaxLen(vector<int> &nums)
	{
		int n = int(nums.size());
		pos.resize(n);
		neg.resize(n);
		if (nums[0] > 0)
			pos[0] = 1;
		else if (nums[0] < 0)
			neg[0] = 1;
		for (int i = 1; i < n; i++)
		{
			if (nums[i] == 0)
			{
				pos[i] = 0;
				neg[i] = 0;
			}
			else if (nums[i] > 0)
			{
				pos[i] = pos[i - 1] > 0 ? pos[i - 1] + 1 : 1;
				neg[i] = neg[i - 1] > 0 ? neg[i - 1] + 1 : 0;
			}
			else
			{
				pos[i] = neg[i - 1] > 0 ? neg[i - 1] + 1 : 0;
				neg[i] = pos[i - 1] > 0 ? pos[i - 1] + 1 : 1;
			}
		}
		return *max_element(pos.begin(), pos.end());
	}
};

int main()
{
	vector<int> nums;
	nums = { 0,1,-2,-3,-4 };
	auto sol = new Solution();
	cout << sol->getMaxLen(nums) << endl;
	return 0;
}
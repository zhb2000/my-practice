//最大相等频率
//https://leetcode-cn.com/problems/maximum-equal-frequency/
//思维题、分类讨论
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

class Solution
{
public:
	int maxEqualFreq(vector<int> &nums)
	{
		int n = int(nums.size());
		auto cnt = vector<int>(int(1e5 + 5));
		int ans = 0;
		int maxv = 1;
		int minv = 1;
		auto vcnt = vector<int>(int(1e5 + 5));
		auto occur = vector<bool>(int(1e5 + 5));
		int occnum = 0;
		for (int i = 0; i < n; i++)
		{
			int num = nums[i];
			if (!occur[num])
			{
				occur[num] = true;
				occnum++;
			}
			int old = cnt[num];
			int nw = old + 1;
			cnt[num] = nw;
			if (old != 0)
				vcnt[old]--;
			vcnt[nw]++;
			maxv = max(maxv, nw);
			if (old == minv && vcnt[minv] == 0)
				minv++;
			else
				minv = min(minv, nw);
			//分四种情况
			if (maxv == minv + 1 && vcnt[maxv] == 1)
			{
				assert(vcnt[minv] == occnum - 1);
				ans = i + 1;
			}
			else if (minv == 1 && maxv > minv && vcnt[maxv] == occnum - 1)
			{
				assert(vcnt[minv] == 1);
				ans = i + 1;
			}
			else if (minv == 1 && maxv == 1 && vcnt[1] == occnum)
				ans = i + 1;
			else if (occnum == 1)
				ans = i + 1;
		}
		assert(ans != 0);
		return ans;
	}
};

int main()
{
	vector<int> nums;
	//nums = { 1,2,3,3,5 };
	//nums = { 2,2,1,1,5,3,3,5 };
	//nums = { 1,1,1,2,2,2,3,3,3,4,4,4,5 };
	//nums = { 1,1,1,2,2,2 };
	nums = { 10,2,8,9,3,8,1,5,2,3,7,6 };
	//nums = { 1,2 };
	//nums = { 1,1 };
	auto sol = new Solution();
	cout << sol->maxEqualFreq(nums) << endl;
	return 0;
}

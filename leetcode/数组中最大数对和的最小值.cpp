//数组中最大数对和的最小值
//https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/
//排序、贪心
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
	int minPairSum(vector<int> &nums)
	{
		sort(nums.begin(), nums.end());
		int ans = 0;
		auto p = nums.begin();
		auto q = nums.end() - 1;
		while (p < q)
		{
			ans = max(ans, *p + *q);
			++p;
			--q;
		}
		return ans;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> nums;
	//nums = { 3,5,2,3 };
	nums = { 3,5,4,2,4,6 };
	cout << sol->minPairSum(nums) << endl;
	return 0;
}

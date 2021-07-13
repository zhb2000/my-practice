//接雨水
//https://leetcode-cn.com/problems/trapping-rain-water/
//DP
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
	int trap(vector<int> &height)
	{
		int n = int(height.size());
		if (n < 3)
			return 0;
		auto left = vector<int>(n);
		auto right = vector<int>(n);
		left[0] = height[0];
		right[n - 1] = height[n - 1];
		for (int i = 1; i < n; i++)
			left[i] = max(left[i - 1], height[i]);
		for (int i = n - 2; i >= 0; i--)
			right[i] = max(right[i + 1], height[i]);
		int ans = 0;
		for (int i = 1; i < n - 1; i++)
		{
			int h = min(left[i - 1], right[i + 1]);
			if (h > height[i])
				ans += h - height[i];
		}
		return ans;
	}
};

int main()
{
	vector<int> height;
	height = { 0,1,0,2,1,0,1,3,2,1,2,1 };
	//height = { 4,2,0,3,2,5 };
	auto sol = new Solution();
	cout << sol->trap(height) << endl;
	return 0;
}

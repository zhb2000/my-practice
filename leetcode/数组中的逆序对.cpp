//数组中的逆序对
//https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/
//分治、归并排序
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
	vector<int> temp;
	int reversePairs(vector<int> &nums)
	{
		return merge_and_count(nums, 0, int(nums.size()));
	}
	//[start, stop)
	int merge_and_count(vector<int> &nums, int start, int stop)
	{
		if (start == stop) //empty
			return 0;
		if (stop - start == 1) //one element
			return 0;
		int mid = (start + stop) / 2;
		//[start, mid), [mid, stop)
		int left_ans = merge_and_count(nums, start, mid);
		int right_ans = merge_and_count(nums, mid, stop);
		int across_ans = 0;
		int smaller = 0; //smaller than current nums[i]
		int i = start;
		int j = mid;
		while (i < mid && j < stop)
		{
			while (j < stop && nums[i] > nums[j])
			{
				smaller++;
				temp.push_back(nums[j]);
				j++;
			}
			across_ans += smaller;
			temp.push_back(nums[i]);
			i++;
		}
		//rest
		if (i < mid)
		{
			while (i < mid)
			{
				across_ans += smaller;
				temp.push_back(nums[i]);
				i++;
			}
		}
		else if (j < stop)
		{
			while (j < stop)
			{
				temp.push_back(nums[j]);
				j++;
			}
		}
		//copy
		assert(int(temp.size()) == stop - start);
		for (int i = 0; i < int(temp.size()); i++)
			nums[start + i] = temp[i];
		temp.clear();
		return left_ans + right_ans + across_ans;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> nums = { 7,5,6,4 };
	nums = {};
	nums = { 1,2 };
	nums = { 2,1 };
	cout << sol->reversePairs(nums) << endl;
	return 0;
}

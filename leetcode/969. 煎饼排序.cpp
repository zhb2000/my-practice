// 969. 煎饼排序
// https://leetcode-cn.com/problems/pancake-sorting/
// 思维题，选择排序

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
	vector<int> pancakeSort(vector<int> &arr)
	{
		vector<int> ans;
		int n = int(arr.size());
		for (int num = n; num >= 1; num--)
		{
			int i = int(find(arr.begin(), arr.begin() + num, num) - arr.begin());
			if (i == num - 1)
				continue;
			if (i > 0)
			{
				reverse(arr.begin(), arr.begin() + i + 1);
				ans.push_back(i + 1);
			}
			assert(arr[0] == num);
			reverse(arr.begin(), arr.begin() + num);
			ans.push_back(num);
		}
		return ans;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> arr = {3, 2, 4, 1};
	cout << sol->pancakeSort(arr) << endl;
	arr = {1, 2, 3};
	cout << sol->pancakeSort(arr) << endl;
	delete sol;
	return 0;
}

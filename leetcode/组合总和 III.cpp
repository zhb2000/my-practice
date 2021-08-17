//组合总和 III
//https://leetcode-cn.com/problems/combination-sum-iii/
//子集枚举（DFS）
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
	vector<int> temp;
	vector<vector<int>> ans;

	vector<vector<int>> combinationSum3(int k, int n)
	{
		dfs(1, k, n);
		return ans;
	}

	void dfs(int num, int res_pos, int want)
	{
		if (res_pos == 0 || want == 0)
		{
			if (res_pos == 0 && want == 0)
			{
				ans.push_back(temp);
				return;
			}
			else
				return;
		}
		if (num > 9)
			return;
		dfs(num + 1, res_pos, want);
		temp.push_back(num);
		dfs(num + 1, res_pos - 1, want - num);
		temp.pop_back();
	}
};

int main()
{
	auto sol = new Solution();
	int k = 3, n = 7;
	auto ans = sol->combinationSum3(k, n);
	cout << ans << endl;
	return 0;
}

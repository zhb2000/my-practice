//组合总和 II
//https://leetcode-cn.com/problems/combination-sum-ii/
//DFS 暴搜（回溯法）
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
	vector<int> cand;
	vector<int> cnt;
	vector<int> temp;
	vector<vector<int>> ans;

	vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
	{
		sort(candidates.begin(), candidates.end());
		for (int i = 0; i < int(candidates.size()); i++)
		{
			if (i - 1 >= 0 && candidates[i] == candidates[i - 1])
				cnt.back()++;
			else
			{
				cand.push_back(candidates[i]);
				cnt.push_back(1);
			}
		}
		assert(cand.size() == cnt.size());
		dfs(0, target);
		return ans;
	}

	void dfs(int i, int want)
	{
		if (i == int(cand.size()))
			return;
		dfs(i + 1, want);
		int sum = 0;
		int k = 0;
		while (k + 1 <= cnt[i])
		{
			temp.push_back(cand[i]);
			sum += cand[i];
			k++;
			if (sum == want)
			{
				ans.push_back(temp);
				break;
			}
			else if (sum > want)
				break;
			dfs(i + 1, want - sum);
		}
		for (int c = 1; c <= k; c++)
			temp.pop_back();
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> cand = { 10,1,2,7,6,1,5 };
	int target = 8;
	auto ans = sol->combinationSum2(cand, target);
	cout << sol->cand << endl;
	cout << ans << endl;
	return 0;
}

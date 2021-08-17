//组合总和
//https://leetcode-cn.com/problems/combination-sum/
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

class Solution
{
public:
	vector<int> candidates;
	vector<int> temp;
	vector<vector<int>> ans;

	vector<vector<int>> combinationSum(vector<int> &candidates, int target)
	{
		this->candidates = candidates;
		dfs(0, target);
		return ans;
	}

	void dfs(int i, int want)
	{
		cout << "dfs(" << i << ", " << want << ")\n";
		if (i == int(candidates.size()))
			return;
		dfs(i + 1, want);
		int sum = 0;
		int k = 1;
		while (true)
		{
			temp.push_back(candidates[i]);
			sum += candidates[i];
			if (sum == want)
			{
				ans.push_back(temp);
				break;
			}
			else if (sum > want)
				break;
			dfs(i + 1, want - sum);
			k++;
		}
		for (int c = 1; c <= k; c++)
			temp.pop_back();
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> candidates = { 2, 3, 6, 7 };
	int target = 7;
	sol->combinationSum(candidates, target);
	return 0;
}

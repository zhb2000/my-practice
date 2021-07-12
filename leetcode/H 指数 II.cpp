//H 指数 II
//https://leetcode-cn.com/problems/h-index-ii/
//二分
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
	int hIndex(vector<int> &citations)
	{
		sort(citations.begin(), citations.end());
		int n = int(citations.size());
		int index = upperbound(citations);
		if (index > 0 && citations[index - 1] == n - (index - 1))
			index = index - 1;
		else if (index >= n)
			index = index - 1;
		return min(citations[index], n - index);
	}

	int upperbound(const vector<int> &citations)
	{
		int n = int(citations.size());
		int l = 0;
		int r = n;
		while (l < r)
		{
			int m = (l + r) / 2;
			double v = double(citations[m]) / (n - m);
			if (v <= 1.0)
				l = m + 1;
			else
				r = m;
		}
		assert(l == r);
		return l;
	}
};

int main()
{
	vector<int> citations = { 3,0,6,1,5 };
	//citations = { 0 };
	//citations = { 100 };
	//citations = { 0,1,4,5,6 };
	//citations = { 0,1,2,5,6 };
	auto sol = new Solution();
	cout << sol->hIndex(citations) << endl;
	return 0;
}

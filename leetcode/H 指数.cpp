//H 指数
//https://leetcode-cn.com/problems/h-index/
//排序、二分
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
		vector<double> v;
		for (int i = 0; i < n; i++)
			v.push_back(double(citations[i]) / (n - i));
		int index = upper_bound(v.begin(), v.end(), 1.0) - v.begin();
		if (index > 0 && citations[index - 1] == n - (index - 1))
			index = index - 1;
		else if (index >= n)
			index = index - 1;
		return min(citations[index], n - index);
	}
};

int main()
{
	vector<int> citations = { 3,0,6,1,5 };
	citations = { 0 };
	//citations = { 100 };
	//citations = { 0,1,4,5,6 };
	//citations = { 0,1,2,5,6 };
	auto sol = new Solution();
	cout << sol->hIndex(citations) << endl;
	return 0;
}

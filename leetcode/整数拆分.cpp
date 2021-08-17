//整数拆分
//https://leetcode-cn.com/problems/integer-break/
//区间 DP
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
	int f_arr[50 + 3];

	int f(int n)
	{
		assert(n >= 1);
		if (n == 1)
			return 1;
		if (f_arr[n] != -1)
			return f_arr[n];
		int ans = 0;
		for (int l = 1; l <= n - 1; l++)
		{
			int lans = max(l, f(l));
			int rans = max(n - l, f(n - l));
			int temp = lans * rans;
			ans = max(ans, temp);
		}
		f_arr[n] = ans;
		return ans;
	}

	int integerBreak(int n)
	{
		memset(f_arr, -1, sizeof(f_arr));
		return f(n);
	}
};

int main()
{
	auto sol = new Solution();
	cout << sol->integerBreak(2) << endl;
	cout << sol->integerBreak(10) << endl;
	return 0;
}

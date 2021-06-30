//279. 完全平方数
//https://leetcode-cn.com/problems/perfect-squares/
//DP
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

using namespace std;

class Solution
{
public:
	static const int maxn = int(1e4 + 3);
	static const int INF = int(1e9);
	int f_arr[maxn];
	vector<int> squares;

	void init(int n)
	{
		fill_n(f_arr, n + 1, 0);
		for (int i = 1; i * i <= n; i++)
			squares.push_back(i * i);
	}

	int numSquares(int n)
	{
		init(n);
		return f(n);
	}

	int f(int n)
	{
		if (n == 0)
			return 0;
		if (f_arr[n] != 0)
			return f_arr[n];
		int ans = INF;
		for (int sq : squares)
		{
			if (n - sq < 0)
				break;
			ans = min(ans, f(n - sq) + 1);
		}
		f_arr[n] = ans;
		return ans;
	}
};

int main()
{
	auto sol = new Solution();
	cout << sol->numSquares(13) << endl;
	return 0;
}
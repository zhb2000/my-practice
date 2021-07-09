//分割回文串 II
//DP、线性 DP
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
	static const int INF = int(1e9);
	static const int maxn = int(2e3 + 5);
	bool is_huiwen[maxn][maxn];
	char s[maxn];
	int f[maxn];
	int n;

	int minCut(string s)
	{
		n = int(s.length());
		strcpy(this->s + 1, s.c_str());
		fill_huiwen();
		return solve() - 1;
	}

	int solve()
	{
		f[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			int ans = INF;
			for (int j = 1; j <= i; j++)
				if (is_huiwen[j][i])
					ans = min(ans, f[j - 1] + 1);
			assert(ans != INF);
			f[i] = ans;
		}
		return f[n];
	}

	void fill_huiwen()
	{
		for (int len = 1; len <= n; len++)
		{
			for (int l = 1; l + len - 1 <= n; l++)
			{
				int r = l + len - 1;
				if (r > n)
					continue;
				if (len == 1)
					is_huiwen[l][r] = true;
				else if (len == 2)
					is_huiwen[l][r] = s[l] == s[r];
				else
					is_huiwen[l][r] = (s[l] == s[r]) && is_huiwen[l + 1][r - 1];
			}
		}
	}
};

int main()
{
	string s = "aab";
	//s = "a";
	//s = "ab";
	auto sol = new Solution();
	cout << sol->minCut(s) << endl;
	return 0;
}
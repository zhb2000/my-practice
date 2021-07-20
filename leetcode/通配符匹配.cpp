//通配符匹配
//https://leetcode-cn.com/problems/wildcard-matching/
//线性 DP
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
	bool isMatch(string s, string p)
	{
		int n = int(s.length());
		int m = int(p.length());
		vector<vector<bool>> f = make_array(n + 3, m + 3);
		string str = " ";
		for (char ch : s)
			str.push_back(ch);
		string pattern = " ";
		for (char ch : p)
			pattern.push_back(ch);

		f[0][0] = true;
		bool all_star = true;
		for (int j = 1; j <= m; j++)
		{
			if (pattern[j] == '*' && all_star)
				f[0][j] = true;
			else
			{
				all_star = false;
				f[0][j] = false;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (pattern[j] == '?')
					f[i][j] = f[i - 1][j - 1];
				else if (pattern[j] == '*')
					f[i][j] = f[i][j - 1] || f[i - 1][j];
				else
					f[i][j] = str[i] == pattern[j] && f[i - 1][j - 1];
			}
		}

		return f[n][m];
	}

	vector<vector<bool>> make_array(int n, int m)
	{
		auto a = vector<vector<bool>>(n);
		for (auto &row : a)
			row.resize(m);
		return a;
	}
};

int main()
{
	string s, p;
	/*s = "aa";
	p = "a";*/

	/*s = "aa";
	p = "*";*/

	s = "cb";
	p = "?a";

	//s = "adceb";
	//p = "*a*b";

	/*s = "acdcb";
	p = "a*c?b";*/

	/*s = "";
	p = "******";*/

	//s = "abcabczzzde";
	//p = "*abc???de*";

	//s = "mississippi";
	//p = "m??*ss*?i*pi";

	//s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
	//p = "a*******b";

	//s = "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb";
	//p = "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb";
	auto sol = new Solution();
	cout << sol->isMatch(s, p) << endl;
	return 0;
}

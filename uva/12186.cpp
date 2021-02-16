// 12186 - Another Crisis

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = ~(1 << 31);
const int maxn = (int)1e5 + 5;
int N, T;
vector<int> sons[maxn];

int dp(int u)
{
	if (sons[u].empty())
		return 1;

	vector<int> vec;
	for (int u_son : sons[u])
		vec.push_back(dp(u_son));
	sort(vec.begin(), vec.end());
	int k = sons[u].size();
	int c = (k*T - 1) / 100 + 1;
	int ans = 0;
	for (int i = 0; i < c; i++)
		ans += vec[i];
	return ans;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	while (scanf("%d%d", &N, &T) == 2 && N != 0 && T != 0)
	{
		for (int i = 0; i <= N; i++)
			sons[i].clear();
		for (int i = 1; i <= N; i++)
		{
			int direct_boss;
			scanf("%d", &direct_boss);
			sons[direct_boss].push_back(i);
		}
		printf("%d\n", dp(0));
	}
	return 0;
}
// 10048 Audiophobia
//#pragma warning(disable: 6031)
//#include "pch.h"

#define LOCAL
//#define DEBUG

#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<tuple>
#include<utility>

using namespace std;
typedef long long LL;

const int maxn = 100 + 3;
const int INF = (int)1e9;
int d[maxn][maxn];
int c, s, q, kase;

void init()
{
	for (int i = 1; i <= c; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (i == j)
				d[i][j] = 0;
			else
				d[i][j] = INF;
		}
	}
}

void floyd()
{
	for (int k = 1; k <= c; k++)
		for (int i = 1; i <= c; i++)
			for (int j = 1; j <= c; j++)
				if (d[i][k] < INF && d[k][j] < INF)
					d[i][j] = min(d[i][j], max(d[i][k], d[k][j]));
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	kase = 1;
	while (scanf("%d%d%d", &c, &s, &q) == 3 && !(c == 0 && s == 0 && q == 0))
	{
		init();
		for (int ct = 1; ct <= s; ct++)
		{
			int a, b, dist;
			scanf("%d%d%d", &a, &b, &dist);
			d[a][b] = d[b][a] = dist;
		}
		floyd();
		if (kase != 1)
			printf("\n");
		printf("Case #%d\n", kase);
		for (int ct = 1; ct <= q; ct++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (d[a][b] == INF)
				printf("no path\n");
			else
				printf("%d\n", d[a][b]);
		}
		kase++;
	}
	
	return 0;
}
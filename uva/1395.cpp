// 1395 Slim Span
//#pragma warning(disable: 6031)
//#include "pch.h"

#define LOCAL

#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<tuple>
#include<utility>

using namespace std;

struct Edge
{
	int a, b, w;
};

const int maxn = 100 + 2;
const int maxm = maxn * maxn / 2;
const int INF = (int)1e9;
Edge edges[maxm];
int rankin[maxm];
int n, m;
int ans = INF;
int fa[maxn];
int ssize[maxn];

int father(int u)
{
	if (fa[u] == u)
		return u;
	fa[u] = father(fa[u]);
	return fa[u];
}

void unionset(int x, int y)
{
	if (father(x) == father(y))
		return;

	if (ssize[x] < ssize[y])
		swap(x, y);
	//y into x
	fa[father(y)] = father(x);
	ssize[father(x)] += ssize[father(y)];
}

void init()
{
	ans = INF;
	for (int i = 0; i < m; i++)
		rankin[i] = i;
}

void init_set()
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		ssize[i] = 1;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	while (scanf("%d%d", &n, &m) == 2 && !(n == 0 && m == 0))
	{
		init();
		for (int i = 0; i < m; i++)
			scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].w);
		sort(rankin, rankin + m, [](int i, int j) {return edges[i].w < edges[j].w; });
		
		//[l,r]
		for (int l = 0; l + (n - 1) - 1 < m; l++)
		{
			init_set();
			int setnum = n;
			int r;
			for (r = l; r < m; r++)
			{
				int a = edges[rankin[r]].a;
				int b = edges[rankin[r]].b;
				if (father(a) != father(b))
					setnum--;
				unionset(a, b);
				if (setnum == 1)
					break;
			}
			if (setnum == 1)
				ans = min(ans, edges[rankin[r]].w - edges[rankin[l]].w);
		}
		
		if (ans == INF)
			printf("-1\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}
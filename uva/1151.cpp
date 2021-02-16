// 1151 Buy or Build
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

struct Vex
{
	int x, y;
};

struct SubNet
{
	int cost;
	vector<int> vexis;//套餐中的点编号
};

const int maxn = 1000 + 2;
const int maxm = maxn * maxn;
const int maxq = 8 + 2;
const int INF = ~(1 << 31);
Edge edges[maxm];//原图所有的边
int rankin[maxm];
Vex vexs[maxn];
SubNet subnets[maxq];
vector<Edge> origin_span;//原图span的边

int fa[maxn];
int setsize[maxn];

int n, q;
int ans = INF;

inline int getcost(const Vex& v1, const Vex& v2)
{
	return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

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

	if (setsize[x] < setsize[y])
		swap(x, y);
	//y into x
	fa[father(y)] = father(x);
	setsize[father(x)] += setsize[father(y)];
}

void init_set()
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		setsize[i] = 1;
	}
}

//rankin[], subnets[].vexi, origin_span, ans
void init()
{
	for (int i = 0; i < n*(n+1)/2; i++)
		rankin[i] = i;
	for (int i = 0; i < q; i++)
		subnets[i].vexis.clear();
	origin_span.clear();
	ans = INF;
}

void calc_origin_span()
{
	int edgeindex = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			Edge& e = edges[edgeindex];
			e.a = i;
			e.b = j;
			e.w = getcost(vexs[i], vexs[j]);
			edgeindex++;
		}
	}
	sort(rankin, rankin + (edgeindex + 1), [](int i, int j) {return edges[i].w < edges[j].w; });
	int setnum = n;
	for (int i = 0; i < edgeindex + 1; i++)
	{
		int a = edges[rankin[i]].a;
		int b = edges[rankin[i]].b;
		if (father(a) != father(b))
		{
			origin_span.push_back(edges[rankin[i]]);
			unionset(a, b);
			setnum--;
			if (setnum == 1)
				break;
		}
	}
}

inline bool select(int i, int ennum)
{
	return ((1 << i) & ennum) != 0;
}

void solve()
{
	for (int ennum = 0; ennum <= (1 << q) - 1; ennum++)//每种方案
	{
		init_set();
		int the_cost = 0;//该种方案的花费
		int setnum = n;
		
		for (int i = 0; i < q && setnum > 1; i++)//使用套餐
		{
			int lastvex = -1;
			if (select(i, ennum))
			{
				the_cost += subnets[i].cost;
				for (int vexi : subnets[i].vexis)
				{
					if (lastvex == -1)
						lastvex = vexi;
					else
						if (father(lastvex) != father(vexi))
						{
							unionset(lastvex, vexi);
							setnum--;
							if (setnum == 1)
								break;
						}
				}
			}
		}
		if (setnum > 1)//仅用当前方案的套餐搞不出span，加边
		{
			for (Edge e : origin_span)
			{
				if (father(e.a) != father(e.b))
				{
					unionset(e.a, e.b);
					the_cost += e.w;
					setnum--;
#ifdef DEBUG
					printf("add edge (%d, %d), w: %d\n", e.a, e.b, e.w);
#endif // DEBUG
					if (setnum == 1)
						break;
				}
			}
		}

#ifdef DEBUG
		printf("buy: ");
		for (int i = q - 1; i >= 0; i--)
		{
			if (select(i, ennum))
				printf("1");
			else
				printf("0");
		}
		printf("; the cost: %d\n", the_cost);
		puts("--------------");
#endif // DEBUG

		ans = min(ans, the_cost);
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	int T;
	cin >> T;
	for (int kase = 1; kase <= T; kase++)
	{
		scanf("%d%d", &n, &q);
		init();
		for (int i = 0; i < q; i++)
		{
			int num;
			scanf("%d", &num);
			scanf("%d", &subnets[i].cost);
			for (int j = 0; j < num; j++)
			{
				int vexnum;
				scanf("%d", &vexnum);
				subnets[i].vexis.push_back(vexnum);
			}
		}
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &vexs[i].x, &vexs[i].y);

		init_set();
		calc_origin_span();
		solve();
		printf("%d\n", ans);
		if (kase < T)
			printf("\n");
	}
	return 0;
}
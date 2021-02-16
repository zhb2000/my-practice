// 658 It's not a Bug, it's a Feature!
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

struct Vex
{
	int status;
	int dist;
	Vex(int status, int dist) :status(status), dist(dist) {}
	bool operator<(const Vex& v) const
	{
		return dist > v.dist;
	}
};

const int maxn = 20 + 3;
const int maxm = 100 + 3;
const int INF = (int)1e9;

char before[maxm][maxn], after[maxm][maxn];
int cost[maxm];

int d[1 << maxn];
int known[1 << maxn];
priority_queue<Vex> pq;

int n, m, kase;

inline bool hasinum(int num, int i)
{
	return (num & (1 << i)) != 0;
}

inline void setinum(int &num, int i, int set)
{
	if (set == 0)
	{
		int mask = ~(1 << i);
		num = num & mask;
	}
	else//set == 1
	{
		int mask = 1 << i;
		num = num | mask;
	}
}

bool can_go(int status, const char *patch_before)
{
	for (int i = 0; i < n; i++)
	{
		char ch = patch_before[i];
		bool has = hasinum(status, i);
		if (ch == '+' && !has)
			return false;
		if (ch == '-' && has)
			return false;
	}
	return true;
}

int go(int status, const char* patch_after)
{
	for (int i = 0; i < n; i++)
	{
		char ch = patch_after[i];
		if (ch == '+')
			setinum(status, i, 1);
		else if (ch == '-')
			setinum(status, i, 0);
	}
	return status;
}

void init()
{
	for (int i = 0; i <= (1 << n) - 1; i++)
	{
		d[i] = INF;
	}
	pq = priority_queue<Vex>();
}

void push_child(int status,int dist)
{
	known[status] = kase;
	for (int pti = 0; pti < m; pti++)
	{
		const char* bef = before[pti];
		const char* aft = after[pti];
		if (can_go(status, bef))
		{
			int go_status = go(status, aft);
			int go_dist = dist + cost[pti];
			if (go_dist < d[go_status])
			{
				d[go_status] = go_dist;
				pq.push(Vex(go_status, go_dist));
			}
		}
	}
}

int dijkstra(int start)
{
	pq.push(Vex(start, 0));
	d[start] = 0;
	while (!pq.empty())
	{
		Vex topv = pq.top(); pq.pop();
		if (topv.status == 0)
			return topv.dist;

		if (known[topv.status] == kase)
			continue;

		push_child(topv.status, topv.dist);
	}
	return -1;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	kase = 1;
	while (scanf("%d%d", &n, &m) == 2 && !(n == 0 && m == 0))
	{
		init();
		for (int i = 0; i < m; i++)
			scanf("%d%s%s", &cost[i], before[i], after[i]);
		int start_status = (1 << n) - 1;
		int ret = dijkstra(start_status);
		/*if (kase != 1)
			printf("\n");*/
		printf("Product %d\n", kase);
		if (ret < 0)
			printf("Bugs cannot be fixed.\n\n");
		else
			printf("Fastest sequence takes %d seconds.\n\n", ret);
		kase++;
	}
	
	return 0;
}
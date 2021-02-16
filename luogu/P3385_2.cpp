//P3385 【模板】负环 (链式前向星存图)
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<functional>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_map>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }

const int maxn = 2000 + 5;
const int maxm = (3000 + 5) * 2;
const int INF = 1000000000;
const int nonep = -1;
int n, m, T;

struct Graph
{
	int e_u[maxm], e_v[maxm], e_w[maxm], e_nxt[maxm];
	int nd_d[maxn], nd_cnt[maxn], nd_head[maxn];
	bool nd_inq[maxn];
	int nei;
	void reset()
	{
		nei = 0;
		fill_n(nd_d + 1, n, INF);
		memset(nd_cnt, 0, sizeof(nd_cnt));
		memset(nd_inq, 0, sizeof(nd_inq));
		memset(nd_head, -1, sizeof(nd_head));
	}
	void add_edge(int from, int to, int w)
	{
		e_u[nei] = from; e_v[nei] = to; e_w[nei] = w;
		e_nxt[nei] = nd_head[from];
		nd_head[from] = nei;
		nei++;
	}
};
Graph G;

bool relax(int e)
{
	int u = G.e_u[e];
	int v = G.e_v[e];
	int w = G.e_w[e];
	if (G.nd_d[u] < INF
		&& G.nd_d[u] + w < G.nd_d[v])
	{
		int oldd = G.nd_d[v];
		G.nd_d[v] = G.nd_d[u] + w;
#ifdef DEBUG
		printf("relax u: %d, v: %d; d: %d -> %d;\n", u, v, oldd, G.nd_d[v]);
#endif // DEBUG

		return true;
	}
#ifdef DEBUG
	printf("fail u: %d, v: %d;\n", u, v);
#endif // DEBUG

	return false;
}
//false：有负环
bool spfa(int start)
{
	queue<int> q;
	G.nd_d[start] = 0;
	q.push(start); G.nd_inq[start] = true;
	while (!q.empty())
	{
		int u = q.front(); q.pop(); G.nd_inq[u] = false;
		for (int e = G.nd_head[u]; e != nonep; e = G.e_nxt[e])
		{
			if (relax(e))
			{
				int v = G.e_v[e];
				if (!G.nd_inq[v])
					q.push(v);
				G.nd_cnt[v]++;
				if (G.nd_cnt[v] >= n)
					return false;
			}
		}
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cin >> T;
	for (int kase = 1; kase <= T; kase++)
	{
#ifdef DEBUG
		printf("kase %d\n", kase);
#endif // DEBUG
		scanf("%d%d", &n, &m);
		G.reset();
		for (int c = 1; c <= m; c++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (w < 0)
				G.add_edge(u, v, w);
			else
			{
				G.add_edge(u, v, w);
				G.add_edge(v, u, w);
			}
		}
		if (!spfa(1))
			puts("YES");
		else
			puts("NO");
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
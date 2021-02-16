//P3385 【模板】负环（vector存图）
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
int n, m;
struct Edge
{
	int u, v, w;
};
struct Node
{
	vector<int> outedges;
	int d;
	bool inq;
	int cnt;
};
struct Graph
{
	Edge edges[maxm];
	Node nodes[maxn];
	int nei;
	void reset()
	{
		nei = 0;
		for (int ui = 1; ui <= n; ui++)
		{
			Node& node = nodes[ui];
			node.cnt = 0;
			node.d = INF;
			node.inq = false;
			node.outedges.clear();
		}
	}
	void add_edge(int ui, int vi, int w)
	{
		edges[nei] = { ui, vi, w };
		nodes[ui].outedges.push_back(nei);
		nei++;
	}
};

Graph G;

bool relax(int ei)
{
	int ui = G.edges[ei].u;
	int vi = G.edges[ei].v;
	int w = G.edges[ei].w;
#ifdef DEBUG
	printf("try u: %d, v: %d, w: %d\n", ui, vi, w);
#endif // DEBUG

	if (G.nodes[ui].d < INF
		&& G.nodes[ui].d + w < G.nodes[vi].d)
	{
		int oldd = G.nodes[vi].d;
		G.nodes[vi].d = G.nodes[ui].d + w;
#ifdef DEBUG
		printf("relax u: %d, v: %d, w: %d\n", ui, vi, w);
		printf("oldd: %d, newd: %d\n", oldd, G.nodes[vi].d);
#endif // DEBUG

		return true;
	}
	return false;
}
//false: 有负环
bool spfa(int s)
{
	queue<int> q;
	G.nodes[s].d = 0;
	q.push(s);
	G.nodes[s].inq = true;
	while (!q.empty())
	{
		int ui = q.front(); Node& u = G.nodes[ui];
		q.pop(); u.inq = false;
		for (int ei : u.outedges)
		{
			Edge& oe = G.edges[ei];
			int vi = oe.v; Node& v = G.nodes[vi];
			if (relax(ei))
			{
				if (!v.inq)
					q.push(vi);
				v.cnt++;
				if (v.cnt >= n)
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

	int T;
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
			int ui, vi, w;
			scanf("%d%d%d", &ui, &vi, &w);
			if (w < 0)
				G.add_edge(ui, vi, w);
			else
			{
				G.add_edge(ui, vi, w);
				G.add_edge(vi, ui, w);
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
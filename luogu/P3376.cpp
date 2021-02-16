//P3376 【模板】网络最大流
//增广路算法
#ifndef LOCAL
#define NDEBUG
#endif // close assert if not local
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
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
#include<cassert>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
template <class Int>
inline Int fast_read()
{
	Int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
inline int readint() { return fast_read<int>(); }
inline ll readll() { return fast_read<ll>(); }
template <class Int>
inline Int avg2(Int a, Int b) { if (a > b) swap(a, b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { if (l > r) swap(l, r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;
//------------------------ header end ------------------------

const ll INF = ll(INTMAX) + 10;

template<int maxN, int maxM>
struct Graph
{
	int e_from[maxM];
	int e_to[maxM];
	ll e_cap[maxM];
	ll e_flow[maxM];

	vector<int> n_out_edges[maxN];
	ll n_a[maxN];
	int n_from_e[maxN];

	int nxt_edge;

	void clear(int topn)
	{
		nxt_edge = 0;
		for (int i = 0; i <= topn; i++)
			n_out_edges[i].clear();
	}

	void add_one_edge(int from, int to, ll cap)
	{
		int e = nxt_edge; nxt_edge++;
		e_from[e] = from;
		e_to[e] = to;
		e_cap[e] = cap;
		e_flow[e] = 0;
		n_out_edges[from].push_back(e);
	}

	void add_edge(int from, int to, ll cap)
	{
		add_one_edge(from, to, cap);
		add_one_edge(to, from, 0);
	}

	ll max_flow(int s, int t, int n)
	{
		ll flow = 0;
		while (true)
		{
			for (int i = 1; i <= n; i++)
				n_a[i] = 0;
			queue<int> q;
			n_a[s] = INF;
			q.push(s);
			while (!q.empty())
			{
				int u = q.front(); q.pop();
				for (int e : n_out_edges[u])
				{
					int v = e_to[e];
					if (n_a[v] == 0 && e_cap[e] > e_flow[e])
					{
						n_from_e[v] = e;
						n_a[v] = min(n_a[u], e_cap[e] - e_flow[e]);
						q.push(v);
					}
				}
				if (n_a[t] > 0)
					break;
			}

			if (n_a[t] == 0)
				break;//return flow

			for (int u = t; u != s; u = e_from[n_from_e[u]])
			{
				int e = n_from_e[u];
				e_flow[e] += n_a[t];
				e_flow[rev_edge(e)] -= n_a[t];
			}
			flow += n_a[t];
		}
		return flow;
	}

	static int rev_edge(int e)
	{
		if (iseven(e))
			return e + 1;
		else
			return e - 1;
	}
};

const int maxn = 200 + 3;
const int maxm = 5000 + 3;
Graph<maxn, maxm * 2> g;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	g.clear(n);
	for (int ct = 1; ct <= m; ct++)
	{
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		g.add_edge(u, v, w);
	}
	printf("%lld", g.max_flow(s, t, n));

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
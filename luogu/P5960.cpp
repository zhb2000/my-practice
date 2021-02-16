//P5960 【模板】差分约束算法
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
#include<cctype>
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
template <class T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
	os << "["; bool isfirst = true;
	for (const auto &x : vec)
	{
		if (isfirst) isfirst = false;
		else os << ", ";
		os << x;
	}
	os << "]"; return os;
}
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")"; return os;
}
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

const int INF = int(1e9);

struct Vertex
{
	int dist;
	bool in_queue;
	int cnt;
	int head;
	void clear()
	{
		dist = INF;
		in_queue = false;
		cnt = 0;
		head = -1;
	}
};

struct Edge
{
	int from;
	int to;
	int weight;
	int nxt;
};

struct Entry
{
	int u;
	int dist;
	bool operator<(const Entry &other) const
	{
		return dist > other.dist;
	}
};

const int maxn = int(5e3) + 5;
const int maxm = int(5e3) + 5;
const int maxe = maxm + maxn;

Vertex vertices[maxn];
Edge edges[maxe];
int ecnt = 0;

void add_edge(int u, int v, int w)
{
	ecnt++;
	int e = ecnt;
	edges[e].from = u;
	edges[e].to = v;
	edges[e].weight = w;
	edges[e].nxt = vertices[u].head;
	vertices[u].head = e;
}

// a - b <= c
void add_constrant(int a, int b, int c)
{
	add_edge(b, a, c);
}

void init(int n)
{
	ecnt = 0;
	for (int u = 0; u <= n; u++)
		vertices[u].clear();
}

bool relax(int e)
{
	int u = edges[e].from;
	int v = edges[e].to;
	int w = edges[e].weight;
	if (vertices[u].dist + w < vertices[v].dist)
	{
		vertices[v].dist = vertices[u].dist + w;
		return true;
	}
	return false;
}

bool spfa(int start, int n)
{
	vertices[start].dist = 0;
	queue<int> q;
	q.push(start);
	vertices[start].in_queue = true;
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		vertices[u].in_queue = false;
		for (int e = vertices[u].head; e != -1; e = edges[e].nxt)
		{
			int v = edges[e].to;
			if (relax(e))
			{
				vertices[v].cnt += 1;
				if (vertices[v].cnt >= n)
					return false;
				else if (!vertices[v].in_queue)
				{
					q.push(v);
					vertices[v].in_queue = true;
				}
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

	int n, m;
	scanf("%d%d", &n, &m);
	init(n);
	for (int ct = 1; ct <= m; ct++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add_constrant(a, b, c);
	}

	const int start = 0;
	for (int u = 1; u <= n; u++)
		add_edge(start, u, 0);
	if (!spfa(start, n + 1))
		printf("NO");
	else
	{
		for (int u = 1; u <= n; u++)
		{
			if (u != 1)
				printf(" ");
			printf("%d", vertices[u].dist);
		}
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

//L2-001 紧急救援
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
	int head;
	int val;
	int dist;
	int fa;
	int path_num;
	int max_sum_before;

	void clear()
	{
		head = -1;
		dist = INF;
		max_sum_before = 0;
	}
};

struct Edge
{
	int from;
	int to;
	int weight;
	int nxt;
};

const int maxn = 500 + 5;
const int maxe = 2 * maxn * maxn;

Vertex vertices[maxn];
Edge edges[maxe];
int ecnt;

void add_edge(int u, int v, int w)
{
	int e = ecnt;
	ecnt++;
	edges[e].from = u;
	edges[e].to = v;
	edges[e].weight = w;
	edges[e].nxt = vertices[u].head;
	vertices[u].head = e;
}

void add_bi_edge(int u, int v, int w)
{
	add_edge(u, v, w);
	add_edge(v, u, w);
}

void init(int topn)
{
	for (int u = 0; u <= topn; u++)
		vertices[u].clear();
	ecnt = 0;
}

struct Entry
{
	int u;
	int dist;
	bool operator<(const Entry &other) const
	{
		return dist > other.dist;
	}
};

bool relax(int u, int v, int w)
{
	if (vertices[u].dist + w < vertices[v].dist)
	{
		vertices[v].dist = vertices[u].dist + w;
		vertices[v].fa = u;
		vertices[v].path_num = vertices[u].path_num;
		vertices[v].max_sum_before = vertices[u].val + vertices[u].max_sum_before;
		return true;
	}
	else if (vertices[u].dist + w == vertices[v].dist)
	{
		vertices[v].path_num += vertices[u].path_num;
		if (vertices[u].val + vertices[u].max_sum_before > vertices[v].max_sum_before)
		{
			vertices[v].max_sum_before = vertices[u].val + vertices[u].max_sum_before;
			vertices[v].fa = u;
		}
		return false;
	}
	return false;
}

void dijkstra(int start, int dest)
{
	vertices[start].dist = 0;
	vertices[start].fa = -1;
	vertices[start].path_num = 1;
	vertices[start].max_sum_before = 0;
	priority_queue<Entry> pq;
	pq.push({ start,0 });
	while (!pq.empty())
	{
		Entry entry = pq.top(); pq.pop();
		int u = entry.u, dist = entry.dist;
		if (dist > vertices[u].dist)
			continue;
		if (u == dest)
			break;
		for (int e = vertices[u].head; e != -1; e = edges[e].nxt)
		{
			int v = edges[e].to;
			int w = edges[e].weight;
			if (relax(u, v, w))
				pq.push({ v,vertices[v].dist });
		}
	}
}

void print_path(int dest)
{
	vector<int> path;
	for (int u = dest; u != -1; u = vertices[u].fa)
		path.push_back(u);
	reverse(path.begin(), path.end());
	bool isfirst = true;
	for (int u : path)
	{
		if (isfirst)
			isfirst = false;
		else
			printf(" ");
		printf("%d", u);
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m, start, dest;
	scanf("%d%d%d%d", &n, &m, &start, &dest);
	init(n);
	for (int u = 0; u < n; u++)
		scanf("%d", &vertices[u].val);
	for (int c = 1; c <= m; c++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_bi_edge(u, v, w);
	}
	dijkstra(start, dest);
	printf("%d %d\n", vertices[dest].path_num, 
		vertices[dest].val + vertices[dest].max_sum_before);
	print_path(dest);
	printf("\n");


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
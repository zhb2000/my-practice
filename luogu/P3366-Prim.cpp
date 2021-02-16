//P3366 【模板】最小生成树
//Prim
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
	//点的距离定义为该点与已加入点之间的最小边权
	int dist;
	int fa; //MST 中该点的父亲
	bool in_tree; //该点是否在 MST 中
	int head;
	void clear()
	{
		dist = INF;
		fa = -1;
		in_tree = false;
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

const int maxn = 5000 + 5;
const int maxm = int(2e5) + 5;
const int maxe = maxm * 2;

Vertex vertices[maxn];
Edge edges[maxe];
int nxte = 1;

void add_edge(int u, int v, int w)
{
	int e = nxte; nxte++;
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

void init(int n)
{
	for (int u = 0; u <= n; u++)
		vertices[u].clear();
	nxte = 1;
}

bool relax(int u, int v, int w)
{
	if (w < vertices[v].dist)
	{
		vertices[v].dist = w;
		vertices[v].fa = u;
		return true;
	}
	return false;
}

//返回 MST 边权之和
int prim()
{
	int result = 0; //MST 边权之和
	vertices[1].dist = 0;
	priority_queue<Entry> pq;
	pq.push({ 1,0 });
	while (!pq.empty())
	{
		Entry entry = pq.top(); pq.pop();
		int u = entry.u, dist = entry.dist;
		if (dist > vertices[u].dist)
			continue;
		vertices[u].in_tree = true;
		result += dist;
		for (int e = vertices[u].head; e != -1; e = edges[e].nxt)
		{
			int v = edges[e].to, w = edges[e].weight;
			//注意，v 可能已在 MST 中
			if (vertices[v].in_tree)
				continue;
			if (relax(u, v, w))
				pq.push({ v,w });
		}
	}
	return result;
}

//检查是否连通
bool check_connect(int n)
{
	for (int u = 1; u <= n; u++)
		if (!vertices[u].in_tree)
			return false;
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
	for (int c = 1; c <= m; c++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_bi_edge(u, v, w);
	}
	int result = prim();
	if (check_connect(n))
		printf("%d", result);
	else
		printf("orz");

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

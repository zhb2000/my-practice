#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LOCAL
#define DEBUG
//#define CONSOLE_PAUSE


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
inline void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
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
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int INF = int(1e8);

struct Edge
{
	int v;
	int w;
};

struct Node
{
	int dist;
	vector<Edge> eout;
	void init()
	{
		dist = INF;
	}
};

const int maxn = int(1e3 + 5);
Node ns[maxn];
int n, m;

struct Entry
{
	int u;
	int dist;
	bool operator<(const Entry &other) const
	{
		return dist > other.dist;
	}
};

bool pq_pop(priority_queue<Entry> &pq, int u, Entry &en)
{
	while (!pq.empty() && pq.top().dist > ns[pq.top().u].dist)
		pq.pop(); //outdated
	if (pq.empty())
		return false;
	int min_dist = pq.top().dist;
	if (ns[u].dist != min_dist)
		return false;
	vector<Entry> temp;
	while (!pq.empty() && pq.top().dist == min_dist && pq.top().u != u)
	{
		temp.push_back(pq.top()); pq.pop(); //pop min_dist
	}
	if (!pq.empty() && pq.top().u == u)
	{
		assert(pq.top().dist == min_dist);
		en = pq.top(); pq.pop();
		for (const auto &entry : temp)
			pq.push(entry);
		return true;
	}
	else
		return false;
}

bool is_dij(const vector<int> &query)
{
	assert(n == int(query.size()));
	for (int u = 1; u <= n; u++)
		ns[u].init();
	priority_queue<Entry> pq;
	int start = query[0];
	ns[start].dist = 0;
	pq.push({ start, 0 });
	for (int i = 0; i < n; i++)
	{
		if (pq.empty())
			return false;
		int u = query[i];
		Entry en;
		if (!pq_pop(pq, u, en))
			return false;
		assert(en.dist == ns[u].dist);
		for (const Edge &e : ns[u].eout)
		{
			if (ns[u].dist + e.w < ns[e.v].dist)
			{
				ns[e.v].dist = ns[u].dist + e.w;
				pq.push({ e.v, ns[e.v].dist });
			}
		}
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	cin >> n >> m;
	for (int c = 1; c <= m; c++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		//biedge
		ns[u].eout.push_back({ v,w });
		ns[v].eout.push_back({ u,w });
	}
	int qnum;
	cin >> qnum;
	vector<int> query;
	for (int q = 1; q <= qnum; q++)
	{
		query.clear();
		for (int i = 1; i <= n; i++)
		{
			int u;
			cin >> u;
			query.push_back(u);
		}
		if (is_dij(query))
			cout << "Yes\n";
		else
			cout << "No\n";
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

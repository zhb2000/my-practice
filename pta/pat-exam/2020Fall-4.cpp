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

const int maxn = 1000 + 3;
const int INF = int(1e9);

struct Edge
{
	int u;
	int v;
	int w;
	int re;
};

struct Node
{
	vector<Edge> out;
	int dist;
	int reward;
	int fa;
	void init()
	{
		dist = INF;
		reward = 0;
		fa = -1;
	}
};

Node ns[maxn];
int topovis[maxn];

void init_query(int n)
{
	for (int u = 0; u < n; u++)
		ns[u].init();
}

struct Entry
{
	int u;
	int dist;
	int reward;
	bool operator<(const Entry &other) const
	{
		if (dist == other.dist)
			return reward < other.reward;
		return dist > other.dist;
	}
};

bool topodfs(int u)
{
	assert(topovis[u] == 0);
	topovis[u] = -1;
	for (const Edge &e : ns[u].out)
	{
		int v = e.v;
		if (topovis[v] == -1)
			return false;
		else if (topovis[v] == 0)
			if (!topodfs(v))
				return false;
	}
	topovis[u] = 1;
	return true;
}

bool can_topo(int n)
{
	for (int u = 0; u < n; u++)
		if (topovis[u] == 0)
			if (!topodfs(u))
				return false;
	return true;
}

vector<int> solve(int start)
{
	priority_queue<Entry> pq;
	ns[start].dist = 0;
	ns[start].reward = 0;
	pq.push({ start, 0, 0 });

	int dest = -1; int dest_dist = INF;
	while (!pq.empty())
	{
		Entry en = pq.top(); pq.pop();
		int u = en.u;
		if (en.dist > ns[u].dist)
			continue;
		if (en.dist == ns[u].dist && en.reward < ns[u].reward)
			continue;
		assert(en.dist == ns[u].dist);
		assert(en.reward == ns[u].reward);

		//cout << "u: " << u << ", dist: " << en.dist << endl;
		if (ns[u].out.size() == 0 && ns[u].dist < dest_dist)
		{
			dest = u;
			dest_dist = ns[u].dist;
			break;
		}

		for (const Edge &e : ns[u].out)
		{
			int v = e.v; int w = e.w; int re = e.re;
			if (ns[u].dist + w < ns[v].dist)
			{
				ns[v].dist = ns[u].dist + w;
				ns[v].reward = ns[u].reward + re;
				ns[v].fa = u;
				pq.push({ v, ns[v].dist, ns[v].reward });
			}
			else if (ns[u].dist + w == ns[v].dist && ns[u].reward + re > ns[v].reward)
			{
				ns[v].dist = ns[u].dist + w;
				ns[v].reward = ns[u].reward + re;
				ns[v].fa = u;
				pq.push({ v, ns[v].dist, ns[v].reward });
			}
		}
	}

	assert(dest != -1);
	vector<int> path;
	for (int p = dest; p != -1; p = ns[p].fa)
		path.push_back(p);
	return path;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	for (int c = 1; c <= m; c++)
	{
		int v, u, w, re;
		cin >> v >> u >> w >> re;
		ns[u].out.push_back({ u, v, w, re });
	}

	bool consistent = can_topo(n);
	if (consistent)
		cout << "Okay.\n";
	else
		cout << "Impossible.\n";

	int qnum;
	cin >> qnum;
	for (int q = 1; q <= qnum; q++)
	{
		int start;
		cin >> start;
		if (!consistent)
		{
			if (ns[start].out.size() == 0)
				cout << "You may take test " << start << " directly.\n";
			else
				cout << "Error.\n";
		}
		else
		{
			init_query(n);
			vector<int> path = solve(start);
			if (path.size() == 1)
				cout << "You may take test " << start << " directly.\n";
			else
			{
				bool isfirst = true;
				for (int p : path)
				{
					if (isfirst)
						isfirst = false;
					else
						cout << "->";
					cout << p;
				}
				cout << '\n';
			}
		}
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

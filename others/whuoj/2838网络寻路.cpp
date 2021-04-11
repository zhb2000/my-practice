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
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int maxn = int(1e4 + 5);
vector<int> G[maxn];
bool mid_node[maxn];
int cnt = 0;

void add_bi_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

void dfs(int src, int u, int has_go)
{
	if (has_go == 3)
	{
		if (!mid_node[u])
			cnt++;
		return;
	}

	if (has_go == 0)
	{
		assert(src == u);
		for (int v : G[u])
			dfs(src, v, has_go + 1);
		return;
	}

	if (u == src)
		return;
	mid_node[u] = true;
	for (int v : G[u])
		dfs(src, v, has_go + 1);
	mid_node[u] = false;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int c = 1; c <= m; c++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_bi_edge(u, v);
	}

	for (int u = 1; u <= n; u++)
	{
		dfs(u, u, 0);
	}

	printf("%d", cnt);

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

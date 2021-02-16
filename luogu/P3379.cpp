//P3379 【模板】最近公共祖先（LCA）
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

const int maxn = 500000 + 5;
vector<int> G[maxn];
int fa[maxn][31];
int depth[maxn];
int lg2[maxn];//lg2[i] = floor(log2(i))

void calc_lg2()
{
	lg2[1] = 0;
	for (int i = 2; i < maxn; i++)
		lg2[i] = lg2[i / 2] + 1;
}

void add_bi_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

void dfs(int u, int father)
{
	fa[u][0] = father;
	depth[u] = (father == -1) ? 0 : depth[father] + 1;
	for (int i = 1; i <= lg2[depth[u]]; i++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u])
		if (v != father)
			dfs(v, u);
}

int lca(int x, int y)
{
	if (depth[x] < depth[y])
		swap(x, y);
	while (depth[x] > depth[y])
		x = fa[x][lg2[depth[x] - depth[y]]];
	if (x == y)
		return y;
	for (int i = lg2[depth[x]]; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	assert(fa[x][0] == fa[y][0]);
	return fa[x][0];
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	calc_lg2();
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	for (int c = 1; c <= n - 1; c++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add_bi_edge(a, b);
	}
	dfs(s, -1);
	for (int c = 1; c <= m; c++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", lca(a, b));
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
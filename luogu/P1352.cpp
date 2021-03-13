//P1352 没有上司的舞会
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

const int maxn = int(6e3 + 5);
vector<int> G[maxn];
int fa[maxn];
int r[maxn];
int f[maxn][2];

void calc_node(int u)
{
	for (int v : G[u])
		calc_node(v);
	int sum = 0;
	for (int v : G[u])
		sum += max(f[v][0], f[v][1]);
	f[u][0] = sum;
	sum = 0;
	for (int v : G[u])
		sum += f[v][0];
	f[u][1] = r[u] + sum;
}

int find_root(int n)
{
	for (int u = 1; u <= n; u++)
		if (fa[u] == 0)
			return u;
	return -1;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int u = 1; u <= n; u++)
		cin >> r[u];
	for (int c = 1; c <= n - 1; c++)
	{
		int l, k;
		cin >> l >> k;
		G[k].push_back(l);
		fa[l] = k;
	}
	int root = find_root(n);
	calc_node(root);
	cout << max(f[root][0], f[root][1]);

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

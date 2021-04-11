//P4316 绿豆蛙的归宿
//记忆化搜索
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
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	os << "["; bool isfirst = true;
	for (const auto& x : vec)
	{
		if (isfirst) isfirst = false;
		else os << ", ";
		os << x;
	}
	os << "]"; return os;
}
template <class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p)
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

struct Edge
{
	int from;
	int to;
	ll weight;
};

const int maxn = int(1e5) + 5;
vector<Edge> G[maxn];
double f_arr[maxn];

void init(int n)
{
	for (int u = 0; u <= n; u++)
		f_arr[u] = -1.0;
}

int n;

double f(int u)
{
	if (f_arr[u] != -1)
		return f_arr[u];
	if (u == n)
		return 0;
	double len_sum = 0;
	for (const auto& e : G[u])
	{
		int v = e.to;
		len_sum += f(v) + e.weight;
	}
	f_arr[u] = len_sum / double(G[u].size());
	return f_arr[u];
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int m;
	scanf("%d%d", &n, &m);
	init(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		G[u].push_back(Edge{ u,v,w });
	}
	printf("%.2lf", f(1));

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

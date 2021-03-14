//P1122 最大子树和
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

const int maxn = 16000 + 5;
ll f[maxn];
ll beauty[maxn];
vector<int> UG[maxn];
vector<int> G[maxn];

void calc_node(int u)
{
	for (int v : G[u])
		calc_node(v);
	ll sum = 0;
	for (int v : G[u])
		sum += max(f[v], 0ll);
	f[u] = beauty[u] + sum;
}

void ug_to_tree(int u, int father)
{
	for (int v : UG[u])
	{
		if (v == father)
			continue;
		G[u].push_back(v);
		ug_to_tree(v, u);
	}
}

ll solve(int n)
{
	ug_to_tree(1, 0);
	calc_node(1);
	ll ans = ll(-1e10);
	for (int u = 1; u <= n; u++)
		ans = max(ans, f[u]);
	return ans;
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
		cin >> beauty[u];
	for (int c = 1; c <= n - 1; c++)
	{
		int a, b;
		cin >> a >> b;
		UG[a].push_back(b);
		UG[b].push_back(a);
	}
	cout << solve(n);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

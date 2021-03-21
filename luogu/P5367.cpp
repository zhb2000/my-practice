//P5367 【模板】康托展开
//线段树
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
void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
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

template<class Int, int maxN>
struct SegTree
{
	static const int maxNode = maxN * 4;
	static int lch(int u) { return u << 1; }
	static int rch(int u) { return (u << 1) + 1; }
	Int sum[maxNode];
	Int tag[maxNode];
	int n;

	void maintain(int u)
	{
		sum[u] = sum[lch(u)] + sum[rch(u)];
	}

	void pushdown(int u, int l, int r)
	{
		assert(l != r);
		int m = avg2(l, r);
		sum[lch(u)] += clen(l, m) * tag[u];
		tag[lch(u)] += tag[u];
		sum[rch(u)] += clen(m + 1, r) * tag[u];
		tag[rch(u)] += tag[u];
		tag[u] = 0;
	}

	Int query(int ql, int qr)
	{
		return recursive_query(ql, qr, 1, 1, n);
	}

	Int recursive_query(int ql, int qr, int u, int l, int r)
	{
		if (ql <= l && r <= qr)
			return sum[u];
		assert(l != r);
		if (tag[u] != 0)
			pushdown(u, l, r);
		Int ans = 0;
		int m = avg2(l, r);
		if (ql <= m)
			ans += recursive_query(ql, qr, lch(u), l, m);
		if (m + 1 <= qr)
			ans += recursive_query(ql, qr, rch(u), m + 1, r);
		return ans;
	}

	void update(int ul, int ur, Int delta)
	{
		recursive_update(ul, ur, delta, 1, 1, n);
	}

	void recursive_update(int ul, int ur, Int delta, int u, int l, int r)
	{
		if (ul <= l && r <= ur)
		{
			sum[u] += clen(l, r) * delta;
			tag[u] += delta;
			return;
		}
		assert(l != r);
		if (tag[u] != 0)
			pushdown(u, l, r);
		int m = avg2(l, r);
		if (ul <= m)
			recursive_update(ul, ur, delta, lch(u), l, m);
		if (m + 1 <= ur)
			recursive_update(ul, ur, delta, rch(u), m + 1, r);
		maintain(u);
	}
};

const int maxn = int(1e6 + 5);
const int mod = 998244353;
int perm[maxn];
SegTree<int, maxn> gt_cnt;
ll fact[maxn];

void calc_fact(int n)
{
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = i * fact[i - 1] % mod;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n;
	cin >> n;
	gt_cnt.n = n;
	calc_fact(n);
	for (int i = 1; i <= n; i++)
		cin >> perm[i];
	for (int i = 1; i <= n; i++)
	{
		int num = perm[i];
		int cur_cnt = gt_cnt.query(num, num);
		gt_cnt.update(num, num, -cur_cnt);
		if (num == n)
			continue;
		gt_cnt.update(num + 1, n, 1);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int num = perm[i];
		ll x = gt_cnt.query(num, num);
		ll this_ans = x * fact[n - i] % mod;
		ans = (ans + this_ans) % mod;
	}
	ans = (ans + 1) % mod;
	cout << ans;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

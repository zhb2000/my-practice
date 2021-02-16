//P3372 【模板】线段树 1
//树状数组+差分，区间更新、区间查询
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

template<class Int, int maxN>
struct BiIndexTree
{
public:
	void build(int n, const Int *a)
	{
		this->n = n;
		for (int i = 1; i <= n; i++)
			bit[i] = 0;
		for (int i = 1; i <= n; i++)
		{
			bit[i] += a[i];
			int j = i + lowbit(i);
			if (j <= n)
				bit[j] += bit[i];
		}
	}

	void single_update(int i, Int delta)
	{
		for (int j = i; j <= n; j += lowbit(j))
			bit[j] += delta;
	}

	Int prefix_sum(int k)
	{
		Int ans = 0;
		for (int i = k; i > 0; i -= lowbit(i))
			ans += bit[i];
		return ans;
	}

	Int range_sum(int l, int r)
	{
		return prefix_sum(r) - prefix_sum(l - 1);
	}

private:
	int n;
	Int bit[maxN];

	static int lowbit(int x) { return x & -x; }
};

template<class Int, int maxN>
struct DoubleBiIndexTree
{
public:
	void build(int n, const Int *a)
	{
		this->n = n;
		for (int i = 1; i <= n; i++)
		{
			origin_d[i] = (i == 1) ? a[i] - 0 : a[i] - a[i - 1];
			origin_dmi[i] = origin_d[i] * i;
		}
		d.build(n, origin_d);
		dmi.build(n, origin_dmi);
	}

	void range_update(int l, int r, Int delta)
	{
		d.single_update(l, delta);
		d.single_update(r + 1, -delta);
		dmi.single_update(l, l * delta);
		dmi.single_update(r + 1, -(r + 1) * delta);
	}

	Int prefix_sum(int k)
	{
		return (k + 1) * d.prefix_sum(k) - dmi.prefix_sum(k);
	}

	Int range_sum(int l, int r)
	{
		return prefix_sum(r) - prefix_sum(l - 1);
	}

private:
	int n;
	Int origin_d[maxN];
	Int origin_dmi[maxN];
	BiIndexTree<Int, maxN> d;
	BiIndexTree<Int, maxN> dmi;

	static int lowbit(int x) { return x & -x; }
};

const int maxn = int(1e5 + 5);
ll arr[maxn];
DoubleBiIndexTree<ll, maxn> tree;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	tree.build(n, arr);
	for (int c = 1; c <= m; c++)
	{
		int op, x, y, k;
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d%d", &x, &y, &k);
			tree.range_update(x, y, k);
		}
		else
		{
			assert(op == 2);
			scanf("%d%d", &x, &y);
			printf("%lld\n", tree.range_sum(x, y));
		}
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
//P3372 【模板】线段树 1
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
struct SegTree
{
public:
	Int data[maxN];
	
	//[1, n]
	void build(int n)
	{
		this->n = n;
		memset(tag, 0, sizeof(tag));
		recursive_build(1, n, 1);
	}
	//[ul, ur]
	void update(int ul, int ur, Int delta)
	{
		recursive_update(ul, ur, delta, 1, n, 1);
	}
	//[ql, qr]
	Int query(int ql, int qr)
	{
		return recursive_query(ql, qr, 1, n, 1);
	}

private:
	//对区间[l, r]建树，u负责管理[l, r]
	void recursive_build(int l, int r, int u)
	{
		if (l == r)
		{
			tree[u] = data[l];
			return;
		}
		int m = avg2(l, r);
		recursive_build(l, m, lch(u));
		recursive_build(m + 1, r, rch(u));
		maintain(u);
	}
	//查询区间[ql, qr]，u负责管理[l, r]
	Int recursive_query(int ql, int qr, int l, int r, int u)
	{
		if (ql <= l && r <= qr)//[ql, qr]包含[l, r]
			return tree[u];
		int m = avg2(l, r);
		if (tag[u] != 0)
			pushdown(l, r, u);
		Int ans = 0;
		if (ql <= m)//[ql, qr]与左儿子[l, m]有交集
			ans += recursive_query(ql, qr, l, m, lch(u));
		if (qr >= m + 1)//[ql, qr]与右儿子[m+1, r]有交集
			ans += recursive_query(ql, qr, m + 1, r, rch(u));
		return ans;
	}
	//更新区间[ul,ur]，delta为更新量，u负责管理[l, r]
	void recursive_update(int ul, int ur, Int delta, int l, int r, int u)
	{
		if (ul <= l && r <= ur)//[ul, ur]包含[l, r]
		{
			tree[u] += clen(l, r) * delta;
			tag[u] += delta;
			return;
		}
		int m = avg2(l, r);
		if (tag[u] != 0)
			pushdown(l, r, u);
		if (ul <= m)//[ul, ur]与左儿子[l, m]有交集
			recursive_update(ul, ur, delta, l, m, lch(u));
		if (ur >= m + 1)//[ul, ur]与右儿子[m+1, r]有交集
			recursive_update(ul, ur, delta, m + 1, r, rch(u));
		maintain(u);
	}
	//用左右孩子的值计算u的值
	void maintain(int u)
	{
		tree[u] = tree[lch(u)] + tree[rch(u)];
	}
	//标记下传，u负责管理[l, r]
	void pushdown(int l, int r, int u)
	{
		assert(l != r);
		int m = avg2(l, r);
		tree[lch(u)] += tag[u] * clen(l, m);
		tree[rch(u)] += tag[u] * clen(m + 1, r);
		tag[lch(u)] += tag[u];
		tag[rch(u)] += tag[u];
		tag[u] = 0;
	}

	static constexpr int maxNodeNum = maxN * 4;
	static int lch(int u) { return u << 1; }
	static int rch(int u) { return (u << 1) | 1; }

	int n;//data[1...n]
	Int tree[maxNodeNum];
	Int tag[maxNodeNum];
};

const int maxn = int(1e5 + 3);
SegTree<ll, maxn> tree;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &tree.data[i]);
	tree.build(n);
	for (int c = 1; c <= m; c++)
	{
		int op, x, y;
		ll k;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
		{
			scanf("%lld", &k);
			tree.update(x, y, k);
		}
		else
			printf("%lld\n", tree.query(x, y));
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
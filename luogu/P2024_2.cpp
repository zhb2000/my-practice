//P2024 [NOI2001]食物链
//带权并查集
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

template<int maxN>
struct UnionFindSet
{
	int fa[maxN];
	int size_[maxN];
	int re[maxN];

	//(father, relation of x and father)
	Pii find(int x)
	{
		if (x != fa[x])
		{
			int root, re_fa_root;
			tie(root, re_fa_root) = find(fa[x]);
			fa[x] = root;
			re[x] = (re[x] + re_fa_root) % 3;
		}
		return { fa[x],re[x] };
	}
	void reset(int topn)
	{
		for (int x = 0; x <= topn; x++)
		{
			fa[x] = x;
			size_[x] = 1;
			re[x] = 0;
		}
	}
	//0: a equals b
	//1: a eats b
	//2: b eats a
	//-1: no relation
	int relation(int a, int b)
	{
		int fa_a, re_a, fa_b, re_b;
		tie(fa_a, re_a) = find(a);
		tie(fa_b, re_b) = find(b);
		if (fa_a != fa_b)
			return -1;
		return (re_a - re_b + 3) % 3;
	}
	//relation(a, b) will be r
	void make_relation(int a, int b, int r)
	{
		assert(relation(a, b) == -1);

		//put tree fa_a into tree fa_b
		int fa_a, re_a, fa_b, re_b;
		tie(fa_a, re_a) = find(a);
		tie(fa_b, re_b) = find(b);
		if (size_[fa_a] > size_[fa_b])
			make_relation(b, a, (-r + 3) % 3);
		else
		{
			fa[fa_a] = fa_b;
			re[fa_a] = (r + re_b - re_a + 3) % 3;
			size_[fa_b] += size_[fa_a];
		}
	}
};

const int maxn = int(5e4 + 5);
UnionFindSet<maxn> uf;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, k;
	scanf("%d%d", &n, &k);
	uf.reset(n);
	int fake = 0;
	for (int ct = 1; ct <= k; ct++)
	{
		int r, x, y;
		scanf("%d%d%d", &r, &x, &y);
		r -= 1;
		if (x > n || y > n)
			fake++;
		else
		{
			int re_xy = uf.relation(x, y);
			if (re_xy != -1)
			{
				if (re_xy != r)
					fake++;
			}
			else
				uf.make_relation(x, y, r);
		}
	}
	printf("%d", fake);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
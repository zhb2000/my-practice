//P3374 【模板】树状数组 1
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
struct BiIndexTree
{
public:
	Int data[maxN];
	
	//[1, n]
	void build(int n)
	{
		this->n = n;
		for (int i = 1; i <= n; i++)
			bit[i] = 0;
		for (int i = 1; i <= n; i++)
		{
			bit[i] += data[i];
			int j = i + lowbit(i);
			if (j <= n)
				bit[j] += bit[i];
		}
	}
	void update(int i, Int delta)
	{
		for (int j = i; j <= n; j += lowbit(j))
			bit[j] += delta;
	}
	//[1, k]
	Int prefix_sum(int k)
	{
		Int ans = 0;
		for (int i = k; i > 0; i -= lowbit(i))
			ans += bit[i];
		return ans;
	}
	//[l, r]
	Int range_sum(int l, int r)
	{
		return prefix_sum(r) - prefix_sum(l - 1);
	}

private:
	Int bit[maxN];
	int n;

	static inline int lowbit(int x) { return x & -x; }
};

const int maxn = int(5e5 + 3);
BiIndexTree<ll, maxn> tree;

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
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			int x;
			ll k;
			scanf("%d%lld", &x, &k);
			tree.update(x, k);
		}
		else
		{
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%lld\n", tree.range_sum(x, y));
		}
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
//P2024 食物链
//种类并查集
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
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
template <class T>
inline bool isodd(T num) { return (num & 1) != 0; }
template <class T>
inline bool iseven(T num) { return (num & 1) == 0; }
inline int clen(int l, int r) { return r - l + 1; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;

template<int maxNum>
struct UnionFindSet
{
	int fa_[maxNum];
	int size_[maxNum];

	void reset()
	{
		for (int x = 0; x < maxNum; x++)
		{
			fa_[x] = x; size_[x] = 1;
		}
	}
	int find(int x)
	{
		if (x != fa_[x])
			fa_[x] = find(fa_[x]);
		return fa_[x];
	}
	void union2(int x, int y)
	{
		int xx = find(x);
		int yy = find(y);
		if (xx == yy)
			return;
		if (size_[xx] < size_[yy])
			swap(xx, yy);
		fa_[yy] = xx;
		size_[xx] += size_[yy];
	}
	bool in_same(int x, int y) { return find(x) == find(y); }
};

const int maxn = int(5e4 + 3);
UnionFindSet<maxn * 3> uf;
int n, k;

inline int food(int x) { return x + n; }
inline int enermy(int x) { return x + n * 2; }

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif


	scanf("%d%d", &n, &k);
	uf.reset();
	int fake = 0;
	for (int ct = 1; ct <= k; ct++)
	{
		int op, a, b;
		scanf("%d%d%d", &op, &a, &b);
		if (a > n || b > n)
		{
			fake++;
			continue;
		}
		if (op == 1)
		{
			if (uf.in_same(food(a), b) || uf.in_same(enermy(a), b))
				fake++;
			else
			{
				uf.union2(a, b);
				uf.union2(food(a), food(b));
				uf.union2(enermy(a), enermy(b));
			}
		}
		else
		{
			if (uf.in_same(a, b) || uf.in_same(enermy(a), b))
				fake++;
			else
			{
				uf.union2(a, enermy(b));
				uf.union2(food(a), b);
				uf.union2(enermy(a), food(b));
			}
		}
	}
	printf("%d\n", fake);

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
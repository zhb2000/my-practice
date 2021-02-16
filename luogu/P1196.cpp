//P1196 [NOI2002]银河英雄传说
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

template <int maxN>
struct UnionFindSet
{
	int fa[maxN];
	int sz[maxN];
	int before[maxN];

	void clear(int topn)
	{
		for (int x = 0; x <= topn; x++)
		{
			fa[x] = x;
			sz[x] = 1;
			before[x] = 0;
		}
	}

	int find(int x)
	{
		if (x != fa[x])
		{
			int old_fa = fa[x];
			fa[x] = find(old_fa);
			before[x] += before[old_fa];
		}
		return fa[x];
	}

	//x group into y group
	void union2(int x, int y)
	{
		int xx = find(x);
		int yy = find(y);
		if (xx == yy)
			return;
		assert(fa[xx] == xx && before[xx] == 0);
		fa[xx] = yy;
		before[xx] = sz[yy];
		sz[yy] += sz[xx];
	}

	bool in_same(int x, int y)
	{
		return find(x) == find(y);
	}

	int relation(int x, int y)
	{
		if (!in_same(x, y))
			return -1;
		//注意，在 in_same 中已经使用 find 对点 x 和点 y 做了路径压缩
		//所以现在 x 和 y 的直接父亲都是 root
		//自然地，before[x] 现在表示 x 在 root 后面几个，before[y] 同理
		return abs(before[x] - before[y]) - 1;
	}
};

const int maxn = 30000 + 5;
UnionFindSet<maxn> uf;

char read_char()
{
	while (true)
	{
		char ch = getchar();
		if (ch != ' ' && ch != '\r' && ch != '\n')
			return ch;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	uf.clear(30000);
	int t;
	scanf("%d", &t);
	for (int c = 1; c <= t; c++)
	{
		char op = read_char();
		int x, y;
		scanf("%d%d", &x, &y);
		if (op == 'M')
			uf.union2(x, y);
		else
		{
			assert(op == 'C');
			printf("%d\n", uf.relation(x, y));
		}
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

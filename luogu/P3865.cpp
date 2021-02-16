//P3865 【模板】ST表
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
inline int readint()
{
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = x * 10 + ch - 48; ch = getchar(); }
	return x * f;
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

//logMax >= log(maxN)
template<class Int, int maxN, int logMax>
struct SparseTable
{
	Int data[maxN];
	Int f[maxN][logMax];
	int log2[maxN];
	void calc_log2()
	{
		log2[1] = 0;
		for (int i = 2; i < maxN; i++)
			log2[i] = log2[i / 2] + 1;
	}
	void build(int topn)
	{
		for (int i = 1; i <= topn; i++)
			f[i][0] = data[i];
		for (int j = 1; j < logMax; j++)
			for (int i = 1; i + (1 << j) - 1 <= topn; i++)
				f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
	}
	//[l, r]
	Int query(int l, int r)
	{
		int s = log2[clen(l, r)];
		return max(f[l][s], f[r - (1 << s) + 1][s]);
	}
};

const int maxn = int(1e5 + 3);
const int logmax = 17;

SparseTable<int, maxn, logmax> st;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	//scanf("%d%d", &n, &m);
	n = readint(); m = readint();
	for (int i = 1; i <= n; i++)
		//scanf("%d", &st.data[i]);
		st.data[i] = readint();
	st.calc_log2();
	st.build(n);
	for (int c = 1; c <= m; c++)
	{
		int l, r;
		//scanf("%d%d", &l, &r);
		l = readint(); r = readint();
		printf("%d\n", st.query(l, r));
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
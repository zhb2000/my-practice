//P1140 相似基因
//线性 DP
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

const int maxn = 100 + 5;
int dp[maxn][maxn];
char sa[maxn];
char sb[maxn];

int mat[5][5] = {
	{5,-1,-2,-1,-3},
	{-1,5,-3,-2,-4},
	{-2,-3,5,-2,-2},
	{-1,-2,-2,5,-1},
	{-3,-4,-2,-1,0}
};

int a2i(char ch)
{
	if (ch == 'A')
		return 0;
	else if (ch == 'C')
		return 1;
	else if (ch == 'G')
		return 2;
	else if (ch == 'T')
		return 3;
	else
	{
		assert(ch == '-');
		return 4;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%s", &n, sa + 1);
	scanf("%d%s", &m, sb + 1);
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		dp[i][0] = dp[i - 1][0] + mat[a2i(sa[i])][a2i('-')];
	for (int j = 1; j <= m; j++)
		dp[0][j] = dp[0][j - 1] + mat[a2i('-')][a2i(sb[j])];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dp[i][j] = max(
				dp[i - 1][j - 1] + mat[a2i(sa[i])][a2i(sb[j])],
				max(dp[i - 1][j] + mat[a2i(sa[i])][a2i('-')],
					dp[i][j - 1] + mat[a2i('-')][a2i(sb[j])]));
	printf("%d", dp[n][m]);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

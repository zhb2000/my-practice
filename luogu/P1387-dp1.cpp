//P1387 最大正方形
//DP 做法 1
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

const int maxn = 100 + 5;
int mat[maxn][maxn];
int dp[maxn][maxn];

int dp_row[maxn][maxn];
int dp_col[maxn][maxn];

void calc_dp_row(int row, int m)
{
	for (int j = 1; j <= m; j++)
	{
		if (mat[row][j] == 0)
			dp_row[row][j] = 0;
		else
			dp_row[row][j] = dp_row[row][j - 1] + 1;
	}
}

void calc_dp_col(int col, int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (mat[i][col] == 0)
			dp_col[i][col] = 0;
		else
			dp_col[i][col] = dp_col[i - 1][col] + 1;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> mat[i][j];

	for (int row = 1; row <= n; row++)
		calc_dp_row(row, m);
	for (int col = 1; col <= m; col++)
		calc_dp_col(col, n);

	for (int i = 1; i <= n; i++)
		dp[i][1] = mat[i][1];
	for (int j = 1; j <= m; j++)
		dp[1][j] = mat[1][j];

	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j <= m; j++)
		{
			if (mat[i][j] == 0)
			{
				dp[i][j] = 0;
				continue;
			}
			dp[i][j] = min({ dp[i - 1][j - 1], dp_row[i][j - 1], dp_col[i - 1][j] }) + 1;
			// dp[i][j] = min({ dp[i - 1][j - 1],dp[i][j - 1],dp[i - 1][j] }) + 1;
		}
	}
	int max_len = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			max_len = max(max_len, dp[i][j]);
	cout << max_len;

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

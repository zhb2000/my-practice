//P1681 最大正方形II
//DP
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

const int maxn = 1500 + 5;
int mat[maxn][maxn];
int dp[maxn][maxn];

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

	for (int i = 1; i <= n; i++)
		dp[i][1] = 1;
	for (int j = 1; j <= m; j++)
		dp[1][j] = 1;

	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j <= m; j++)
		{
			if (mat[i][j] == mat[i - 1][j - 1] && mat[i][j] != mat[i][j - 1] && mat[i][j] != mat[i - 1][j])
				dp[i][j] = min({ dp[i - 1][j - 1],dp[i][j - 1],dp[i - 1][j] }) + 1;
			else
				dp[i][j] = 1;
		}
	}
	int max_len = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			max_len = max(max_len, dp[i][j]);
	cout << max_len;

#ifdef DEBUG
	cout << "\ndp:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << dp[i][j] << ' ';
		cout << '\n';
	}
#endif // DEBUG



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

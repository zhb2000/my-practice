//P7074 [CSP-J2020] 方格取数
//棋盘 DP
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
inline void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
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

const int maxn = int(1e3 + 5);
ll mat[maxn][maxn];
ll f[maxn][maxn][2];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> mat[i][j];

	for (int i = 1; i <= n; i++)
		f[i][1][0] = f[i][1][1] = mat[i][1] + f[i - 1][1][0];
	for (int j = 2; j <= m; j++)
	{
		f[1][j][0] = mat[1][j] + max(f[1][j - 1][0], f[1][j - 1][1]);
		for (int i = 2; i <= n; i++)
		{
			ll left_ans = max(f[i][j - 1][0], f[i][j - 1][1]);
			f[i][j][0] = mat[i][j] + max(left_ans, f[i - 1][j][0]);
		}
		f[n][j][1] = mat[n][j] + max(f[n][j - 1][0], f[n][j - 1][1]);
		for (int i = n - 1; i >= 1; i--)
		{
			ll left_ans = max(f[i][j - 1][0], f[i][j - 1][1]);
			f[i][j][1] = mat[i][j] + max(left_ans, f[i + 1][j][1]);
		}
	}
	cout << f[n][m][0];

#ifdef DEBUG
	cout << "\n0:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << f[i][j][0] << ' ';
		cout << '\n';
	}
	cout << "\n1:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << f[i][j][1] << ' ';
		cout << '\n';
	}
#endif // DEBUG


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

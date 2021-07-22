//P2051 [AHOI2009]中国象棋
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

const int mod = 9999973;
const int maxn = 100 + 3;
ll f[maxn][maxn][maxn];

ll cm2(ll m)
{
	assert(m >= 2);
	return (m * (m - 1) / 2) % mod;
}

void update(ll i, ll x, ll y)
{
	ll cur = f[i][x][y];
	f[i + 1][x][y] = (f[i + 1][x][y] + cur) % mod;
	if (x >= 1)
		f[i + 1][x - 1][y + 1] = (f[i + 1][x - 1][y + 1] + cur * x % mod) % mod;
	if (y >= 1)
		f[i + 1][x][y - 1] = (f[i + 1][x][y - 1] + cur * y % mod) % mod;
	if (x >= 2)
		f[i + 1][x - 2][y + 2] = (f[i + 1][x - 2][y + 2] + cur * cm2(x) % mod) % mod;
	if (y >= 2)
		f[i + 1][x][y - 2] = (f[i + 1][x][y - 2] + cur * cm2(y) % mod) % mod;
	if (x >= 1 && y >= 1)
		f[i + 1][x - 1][y] = (f[i + 1][x - 1][y] + cur * x * y % mod) % mod;
}

void print_mat(int m, int i)
{
	for (int x = 0; x <= m; x++)
	{
		for (int y = 0; y <= m; y++)
		{
			if (f[i][x][y] == 0)
				continue;
			cout << "f[" << i << "," << x << "," << y << "," << m - x - y << "]=" << f[i][x][y] << " ";
		}
	}
	cout << '\n';
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;

	//put 0
	f[1][m][0] = 1;
	update(1, m, 0);
	//put 1
	f[1][m - 1][1] = m;
	update(1, m - 1, 1);
	//put 2
	if (m >= 2)
	{
		f[1][m - 2][2] = cm2(m);
		update(1, m - 2, 2);
	}

	for (int i = 2; i < n; i++)
	{
		for (int x = 0; x <= m; x++)
		{
			for (int y = 0; y <= m - x; y++)
			{
				if (f[i][x][y] == 0)
					continue;
				update(i, x, y);
			}
		}
	}

	/*print_mat(m, 1);
	cout << endl;
	print_mat(m, 2);
	cout << endl;*/

	ll ans = 0;
	for (int x = 0; x <= m; x++)
	{
		for (int y = 0; y <= m; y++)
		{
			if (x + y > m)
				break;
			ans = (ans + f[n][x][y]) % mod;
		}
	}
	cout << ans;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

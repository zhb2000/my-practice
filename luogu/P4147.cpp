//P4147 玉蟾宫
//悬线法
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

const int maxn = 1000 + 5;
int h[maxn];
int left_most[maxn];
int right_most[maxn];
char mat[maxn][maxn];
int dp[maxn][maxn];

int solve_row(int m)
{
	for (int i = 1; i <= m; i++)
	{
		int l = i;
		while (l >= 1 && h[l] >= h[i])
		{
			left_most[i] = l;
			if (left_most[l] != l)
			{
				assert(left_most[l] < l);
				left_most[i] = left_most[l];
				l = left_most[i] - 1;
			}
			else
				l -= 1;
		}
	}
	for (int i = m; i >= 1; i--)
	{
		int r = i;
		while (r <= m && h[r] >= h[i])
		{
			right_most[i] = r;
			if (right_most[r] != r)
			{
				assert(right_most[r] > r);
				right_most[i] = right_most[r];
				r = right_most[r] + 1;
			}
			else
				r += 1;
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		int temp_ans = (right_most[i] - left_most[i] + 1) * h[i];
		ans = max(ans, temp_ans);
	}
	return ans;
}


int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> mat[i][j];

	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j <= m; j++)
		{
			if (mat[i][j] != 'F')
				dp[i][j] = 0;
			else
				dp[i][j] = dp[i + 1][j] + 1;
		}
	}

	int ans = 0;
	for (int row = 1; row <= n; row++)
	{
		for (int j = 1; j <= m; j++)
			h[j] = dp[row][j];
		ans = max(ans, solve_row(m));
	}

	cout << ans * 3;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

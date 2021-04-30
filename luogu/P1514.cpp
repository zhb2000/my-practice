//P1514 [NOIP2010 提高组] 引水入城
//贪心、排序、记忆化搜索
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
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	os << "["; bool isfirst = true;
	for (const auto& x : vec)
	{
		if (isfirst) isfirst = false;
		else os << ", ";
		os << x;
	}
	os << "]"; return os;
}
template <class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p)
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

struct Interval
{
	int l, r;
	Interval(int l, int r) :l(l), r(r) {}
	bool operator<(const Interval& other) const
	{
		if (l == other.l)
		{
			int tlen = clen(l, r);
			int olen = clen(other.l, other.r);
			return tlen > olen;
		}
		return l < other.l;
	}
};

const int maxn = 500 + 3;
const int INF = int(1e6 + 3);
int n, m;
int mat[maxn][maxn];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int lmost[maxn][maxn];
int rmost[maxn][maxn];
bool vis[maxn][maxn];

bool in_bound(int i, int j)
{
	return 0 <= i && i < n && 0 <= j && j < m;
}

void dfs(int i, int j)
{
	vis[i][j] = true;
	if (i == n - 1)
	{
		lmost[i][j] = j;
		rmost[i][j] = j;
	}
	for (int index = 0; index < 4; index++)
	{
		int ni = i + dx[index];
		int nj = j + dy[index];
		if (in_bound(ni, nj) && mat[ni][nj] < mat[i][j])
		{
			if (!vis[ni][nj])
				dfs(ni, nj);
			lmost[i][j] = min(lmost[i][j], lmost[ni][nj]);
			rmost[i][j] = max(rmost[i][j], rmost[ni][nj]);
		}
	}
}

int solve_cover(const vector<Interval>& x)
{
	int sz = int(x.size());
	int fix = 0;
	int sel = -1;
	int ans = 1;
	for (int i = 1; i < sz; i++)
	{
		assert(x[i].l <= x[fix].r + 1);
		if (x[i].r > x[fix].r)
		{
			if (sel == -1)
			{
				sel = i;
				ans += 1;
			}
			else if (x[i].r > x[sel].r)
				sel = i;
		}
		if (i + 1 < sz and x[i + 1].l > x[fix].r + 1)
		{
			if (sel != -1)
			{
				fix = sel;
				sel = -1;
			}

		}
	}
	return ans;
}

void init()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			lmost[i][j] = INF;
			rmost[i][j] = -1;
			vis[i][j] = false;
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	cin >> n >> m;
	init();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> mat[i][j];
	vector<Interval> intervals;
	for (int j = 0; j < m; j++)
	{
		dfs(0, j);
		if (rmost[0][j] != -1)
			intervals.push_back({ lmost[0][j],rmost[0][j] });
	}
	int last_not_vis = 0;
	for (int j = 0; j < m; j++)
		if (!vis[n - 1][j])
			last_not_vis++;
	if (last_not_vis > 0)
	{
		cout << 0 << '\n';
		cout << last_not_vis;
		return 0;
	}
	sort(intervals.begin(), intervals.end());
	cout << 1 << '\n';
	cout << solve_cover(intervals);

	/*cout << '\n';
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << lmost[i][j] << ' ';
		cout << '\n';
	}*/

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

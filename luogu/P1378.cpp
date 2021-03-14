//P1378 油滴扩展
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

const double PI = 3.1415926;
const int maxn = 6 + 5;
double radius[maxn];
double px[maxn];
double py[maxn];
bool vis[maxn];
vector<int> seq;
double rec_l, rec_r, rec_u, rec_d;
double ans = 0.0;

void set_rec(double x1, double y1, double x2, double y2)
{
	rec_l = min(y1, y2);
	rec_r = max(y1, y2);
	rec_u = min(x1, x2);
	rec_d = max(x1, x2);
}

double dist(double x1, double y1, double x2, double y2)
{
	double dx = fabs(x1 - x2);
	double dy = fabs(y1 - y2);
	return sqrt(dx * dx + dy * dy);
}

void calc_point_radius(int i, int n)
{
	assert(radius[i] < 0);
	double x = px[i], y = py[i];
	vector<double> candidates =
	{
		x - rec_u,
		rec_d - x,
		y - rec_l,
		rec_r - y
	};
	for (int j = 1; j <= n; j++)
	{
		if (j != i && radius[j] >= 0)
		{
			double dst = dist(x, y, px[j], py[j]);
			double rest_r = dst - radius[j];
			if (rest_r > 0)
				candidates.push_back(rest_r);
			else
				candidates.push_back(0.0);
		}
	}
	double min_r = 1e9;
	for (double candidate : candidates)
		min_r = min(min_r, candidate);
	radius[i] = min_r;
}

void solve(int n)
{
	assert(int(seq.size()) == n);
	for (int i = 1; i <= n; i++)
		radius[i] = -1.0;
	for (int i : seq)
		calc_point_radius(i, n);
	double temp_ans = 0.0;
	for (int i = 1; i <= n; i++)
		temp_ans += PI * radius[i] * radius[i];
	ans = max(ans, temp_ans);
}

void dfs(int u, int n)
{
	assert(!vis[u]);
	seq.push_back(u);
	vis[u] = true;
	if (int(seq.size()) == n)
		solve(n);
	else
	{
		for (int v = 1; v <= n; v++)
			if (!vis[v])
				dfs(v, n);
	}
	assert(vis[u] && seq.back() == u);
	seq.pop_back();
	vis[u] = false;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	double x1, y1, x2, y2;
	scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	set_rec(x1, y1, x2, y2);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &px[i], &py[i]);
	for (int u = 1; u <= n; u++)
		dfs(u, n);
	double rec_area = (rec_r - rec_l) * (rec_d - rec_u);
	printf("%.0lf", rec_area - ans);



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

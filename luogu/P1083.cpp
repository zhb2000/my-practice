//P1083 [NOIP2012 提高组] 借教室
//二分答案、差分、前缀和
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

const int maxn = int(1e6 + 5);
int n, m;
ll arr[maxn];
ll diff[maxn];
ll d[maxn];
ll s[maxn];
ll t[maxn];

bool check(int m)
{
	fill(diff + 1, diff + 1 + n, 0);
	for (int i = 1; i <= m; i++)
	{
		diff[s[i]] += d[i];
		diff[t[i] + 1] -= d[i];
	}
	ll last = 0;
	for (int i = 1; i <= n; i++)
	{
		ll presum = last + diff[i];
		if (presum > arr[i])
			return false;
		last = presum;
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	for (int j = 1; j <= m; j++)
		cin >> d[j] >> s[j] >> t[j];
	int l = 1;
	int r = n + 1;
	while (l < r)
	{
		int m = avg2(l, r);
		//printf("l: %d, r: %d, m: %d, check: %d\n", l, r, m, check(m));
		if (check(m))
			l = m + 1;
		else
			r = m;
	}
	assert(l == r);
	if (l == n + 1)
	{
		cout << 0;
	}
	else
	{
		cout << -1 << '\n' << l;
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

//P1417 烹调方案
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
void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
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

struct Food
{
	ll a, b, c;
	bool operator>(const Food &other) const
	{
		return b * other.c > other.b * c;
	}
};

const int maxn = 50 + 5;
const int maxT = int(1e5 + 5);
Food arr[maxn];
ll f[maxT];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	ll T, n;
	cin >> T >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i].a;
	for (int i = 1; i <= n; i++)
		cin >> arr[i].b;
	for (int i = 1; i <= n; i++)
		cin >> arr[i].c;
	sort(arr + 1, arr + 1 + n, [](const Food &x, const Food &y) { return x > y; });
	for (int i = 1; i <= n; i++)
	{
		for (int j = int(T); j >= arr[i].c; j--)
			f[j] = max(f[j], f[j - arr[i].c] + arr[i].a - arr[i].b * j);
		for (int j = 1; j <= T; j++)
			f[j] = max(f[j - 1], f[j]);
	}
	cout << f[T];

	/*ll ans = 0;
	for (int i = 0; i <= T; i++)
		ans = max(ans, f[i]);
	cout << ans;*/


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

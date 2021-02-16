//L1-009 N个数求和
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

template<class Int>
Int gcd(Int a, Int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

template<class Int>
Int lcm(Int a, Int b)
{
	return a / gcd(a, b) * b;
}

const int maxn = 100 + 5;
// a / b
ll a_arr[maxn];
ll b_arr[maxn];

ll get_b_lcm(int n)
{
	if (n == 1)
		return b_arr[0];
	ll lc = lcm(b_arr[0], b_arr[1]);
	for (int i = 2; i < n; i++)
		lc = lcm(lc, b_arr[i]);
	return lc;
}

void b_to_common(int n, ll b_lcm)
{
	for (int i = 0; i < n; i++)
	{
		ll x = b_lcm / b_arr[i];
		a_arr[i] *= x;
		b_arr[i] = b_lcm;
	}
}

void print_ans(ll a, ll b)
{
	ll x = gcd(abs(a), abs(b));
	a /= x;
	b /= x;
	if (a == 0)
	{
		printf("0\n");
	}
	else if (a % b == 0)
	{
		printf("%lld\n", a / b);
	}
	else if (a / b == 0)
	{
		printf("%lld/%lld\n", a, b);
	}
	else
	{
		printf("%lld %lld/%lld\n", a / b, a % b, b);
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		ll a, b;
		scanf("%lld/%lld", &a, &b);
		ll x = gcd(abs(a), abs(b));
		a /= x;
		b /= x;
		a_arr[i] = a;
		b_arr[i] = b;
	}
	b_to_common(n, get_b_lcm(n));
	ll b_common = b_arr[0];
	ll a_sum = 0;
	for (int i = 0; i < n; i++)
		a_sum += a_arr[i];
	print_ans(a_sum, b_common);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
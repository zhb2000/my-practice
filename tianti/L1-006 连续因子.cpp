//L1-006 连续因子
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

//(first, len)
Pii solve(ll n)
{
	ll first = 0;
	int maxlen = 0;
	ll maxnum = ll(sqrt(n));
	for (ll i = 2; i <= maxnum; i++)
	{
		ll temp = 1;
		ll sel_j = 0;
		for (ll j = i; j <= maxnum; j++)
		{
			temp *= j;
			if (n % temp != 0)
				break;
			else
				sel_j = j;
		}
		if (sel_j == 0)
			continue;
		int len = int(clen(i, sel_j));
		if (len > maxlen)
		{
			maxlen = len;
			first = i;
		}
	}
	if (first == 0)
		return { int(n),1 };
	else
		return { int(first),maxlen };
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ll n;
	scanf("%lld", &n);
	int first, len;
	tie(first, len) = solve(n);
	printf("%d\n", len);
	bool isfirst = true;
	for (int i = 0; i < len; i++)
	{
		if (isfirst)
			isfirst = false;
		else
			printf("*");
		printf("%d", first + i);
	}
	printf("\n");

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
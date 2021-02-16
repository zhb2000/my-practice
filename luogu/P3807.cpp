//P3807 【模板】卢卡斯定理
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
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
template <class T>
inline bool isodd(T num) { return (num & 1) != 0; }
template <class T>
inline bool iseven(T num) { return (num & 1) == 0; }
inline int clen(int l, int r) { return r - l + 1; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;

const int maxp = int(1e5 + 3);
int fact[maxp];

inline void calc_fact(int p)
{
	fact[0] = 1;
	for (int i = 1; i < p; i++)
		fact[i] = ll(fact[i - 1]) * i % p;
}

inline ll quick_pow(ll a, ll n, ll m)
{
	ll res = 1 % m;
	a = a % m;
	while (n > 0)
	{
		if ((n & 1) != 0)
			res = res * a % m;
		a = (a % m) * (a % m) % m;
		n = n >> 1;
	}
	return res;
}

inline int inv(int a, int p) { return int(quick_pow(a, p - 2, p)); }

inline int comb(int n, int m, int p)
{
	if (m > n)
		return 0;
	return ll(fact[n]) * inv(fact[m], p) % p * inv(fact[n - m], p) % p;
}

int lucas(int n, int m, int p)
{
	if (m == 0)
		return 1;
	return ll(comb(n % p, m % p, p)) * lucas(n / p, m / p, p) % p;
}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++)
	{
		int n, m, p;
		scanf("%d%d%d", &n, &m, &p);
		calc_fact(p);
		printf("%d\n", lucas(n + m, n, p));
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
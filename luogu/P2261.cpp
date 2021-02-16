//P2261 余数求和
//整除分块
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

inline ll solve(ll n, ll k)
{
	ll ans = n * k;
	ll temp = 0;
	for (ll l = 1, r; l <= n; l = r + 1)
	{
		if (k / l != 0)
			r = min(k / (k / l), n);
		else
			r = n;
		temp += (k / l) * ((l + r) * (r - l + 1) / 2);
	}
	ans -= temp;
	return ans;
}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ll n, k;
	scanf("%lld%lld", &n, &k);
	printf("%lld", solve(n, k));

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
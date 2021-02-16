//10791 Minimum Sum LCM
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
typedef pair<int, int> pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
template <class T>
inline T isodd(T num) { return (num & 1) != 0; }
template <class T>
inline T iseven(T num) { return (num & 1) == 0; }
inline int clen(int l, int r) { return r - l + 1; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;

ll solve(ll n)
{
	if (n == 1)
		return 2;
	ll ans = 0;
	int pfnum = 0;
	for (int factor = 2; factor <= round(sqrt(n)); factor++)
	{
		if (n % factor == 0)
		{
			pfnum++;
			int part = 1;
			while (n % factor == 0)
			{
				n /= factor;
				part *= factor;
			}
			ans += part;
		}
	}
	if (n > 1)//param n is prime
	{
		pfnum++;
		ans += n;
	}
	if (pfnum == 1)
		ans += 1;
	return ans;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ll n;
	int kase = 1;
	while (scanf("%lld", &n) && n != 0)
	{
		printf("Case %d: %lld\n", kase, solve(n));
		kase++;
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
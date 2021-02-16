//11582 Colossal Fibonacci Numbers!
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
const double EPS = 1e-7;

const int maxn = 1000 + 2;
const int maxlen = 3000 + 5;
vector<int> fibs[maxn];
int lens[maxn];

int quick_pow(ull a, ull n, int m)
{
	if (n == 0)
		return 1 % m;
	ull x = quick_pow(a, n / 2, m);
	int ans = x * x % m;
	if (iseven(n))
		return ans;
	else
		return (ans * a) % m;
}

int solve(ull a, ull b, int n)
{
	if (n == 1 || a == 0)
		return 0;

	if (lens[n] == 0)
	{
		fibs[n].reserve(maxlen);
		fibs[n].push_back(0);
		fibs[n].push_back(1);
		for (int i = 2;; i++)
		{
			int num = (fibs[n][i - 1] + fibs[n][i - 2]) % n;
			fibs[n].push_back(num);
			if (fibs[n][i - 1] == 0 && fibs[n][i] == 1)
			{
				lens[n] = i - 2 + 1;
				break;
			}
		}
	}
	return fibs[n][quick_pow(a % lens[n], b, lens[n])];
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
		ull a, b;
		int n;
		scanf("%llu%llu%d", &a, &b, &n);
		printf("%d\n", solve(a, b, n));
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
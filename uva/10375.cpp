//10375 Choose and divide
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

const int maxsize = int(1e4);
const int maxn = int(1e4 + 5);
int e[maxsize];//每个质因数的指数，用来表示结果
bool is_composite[maxn];
vector<int> primes;

void calc(int n)
{
	for (int b = 2; b <= n; b++)
	{
		if (!is_composite[b])
			primes.push_back(b);
		for (int p : primes)
		{
			if (p * b > n)
				break;
			is_composite[p * b] = true;
			if (b % p == 0)
				break;
		}
	}
}

inline void init()
{
	memset(e, 0, sizeof(e));
}

//给结果乘上 n^d
inline void mult_int(int n, int d)
{
	int num = n;
	for (int i = 0; i < int(primes.size()); i++)
	{
		int factor = primes[i];
		while (num % factor == 0)
		{
			num /= factor;
			e[i] += d;
		}
		if (num == 1)
			break;
	}
}

//给结果乘上 (n!)^d
inline void mult_fract(int n, int d)
{
	for (int num = 1; num <= n; num++)
		mult_int(num, d);
}

double solve(int p, int q, int r, int s)
{
	init();
	mult_fract(p, 1);
	mult_fract(q, -1);
	mult_fract(p - q, -1);
	mult_fract(s, 1);
	mult_fract(r - s, 1);
	mult_fract(r, -1);
	double ans = 1;
	for (int i = 0; i < int(primes.size()); i++)
		ans *= pow(primes[i], e[i]);
	return ans;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	calc(int(1e4 + 2));
	int p, q, r, s;
	while (scanf("%d%d%d%d", &p, &q, &r, &s) == 4)
	{
		printf("%.5lf\n", solve(p, q, r, s));
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
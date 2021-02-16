// P3811 【模板】乘法逆元
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
inline bool isodd(T num) { return (num & 1) != 0; }
template <class T>
inline bool iseven(T num) { return (num & 1) == 0; }
inline int clen(int l, int r) { return r - l + 1; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;

const int maxn = int(3e6 + 5);
int inv[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, p;
	scanf("%d%d", &n, &p);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i)
		inv[i] = ll(p - p / i) * inv[p % i] % p;
	for (int i = 1; i <= n; i++)
		printf("%d\n", inv[i]);

	

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
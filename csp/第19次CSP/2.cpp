//稀疏向量
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

const int maxlen = int(5e5 + 5);
using Elem = pair<int, ll>;
Elem vecu[maxlen], vecv[maxlen];


int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= a; i++)
		scanf("%d%lld", &vecu[i].first, &vecu[i].second);
	for (int i = 1; i <= b; i++)
		scanf("%d%lld", &vecv[i].first, &vecv[i].second);

	ll ans = 0;
	int i = 1, j = 1;
	while (i <= a && j <= b)
	{
		if (vecu[i].first == vecv[j].first)
		{
			ans += vecu[i].second * vecv[j].second;
			i++; j++;
		}
		else if (vecu[i].first < vecv[j].first)
		{
			i++;
		}
		else
		{
			j++;
		}
	}
	printf("%lld", ans);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
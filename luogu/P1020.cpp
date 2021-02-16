//P1020 导弹拦截
//最长上升子序列 O(nlogn) 做法
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
inline Int quick_read()
{
	Int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
inline int readint() { return quick_read<int>(); }
inline ll readll() { return quick_read<ll>(); }
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


const int maxn = 100000 + 3;
int arr[maxn];
int d[maxn];

int solve1(int n)
{
	if (n == 0)
		return 0;
	d[1] = arr[1];
	int len = 1;
	for (int i = 2; i <= n; i++)
	{
		int index = upper_bound(d + 1, d + 1 + len, arr[i]) - d;
		d[index] = arr[i];
		len = max(len, index);
	}
	return len;
}

int solve2(int n)
{
	if (n == 0)
		return 0;
	d[1] = arr[1];
	int len = 1;
	for (int i = 2; i <= n; i++)
	{
		int index = lower_bound(d + 1, d + 1 + len, arr[i]) - d;
		d[index] = arr[i];
		len = max(len, index);
	}
	return len;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int num;
	int i = 1;
	while (scanf("%d", &num) != EOF)
	{
		arr[i] = num;
		i++;
	}
	int n = i - 1;
	int ans2 = solve2(n);
	reverse(arr + 1, arr + 1 + n);
	int ans1 = solve1(n);
	printf("%d\n%d", ans1, ans2);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
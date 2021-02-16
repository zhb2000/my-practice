//P1880 [NOI1995]石子合并
//区间 DP
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

const int INF = int(1e9);
const int maxn = 100 + 5;
int dp_min[maxn * 2][maxn * 2];
int dp_max[maxn * 2][maxn * 2];
int arr[maxn * 2];
int prefix_sum[maxn * 2];

void calc_prefix_sum(int n)
{
	prefix_sum[0] = 0;
	for (int i = 1; i <= 2 * n - 1; i++)
		prefix_sum[i] = prefix_sum[i - 1] + arr[i];
}

//[x, y]
int sum(int x, int y)
{
	return prefix_sum[y] - prefix_sum[x - 1];
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		arr[i] = arr[n + i] = a;
	}
	calc_prefix_sum(n);
	for (int len = 2; len <= n; len++)
	{
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			int j = i + len - 1;
			int temp_min = INF;
			int temp_max = 0;
			//merge [i, k] and [k + 1, j]
			for (int k = i; k < j && k <= 2 * n - 1; k++)
			{
				temp_min = min(temp_min, dp_min[i][k] + dp_min[k + 1][j] + sum(i, j));
				temp_max = max(temp_max, dp_max[i][k] + dp_max[k + 1][j] + sum(i, j));
			}
			dp_min[i][j] = temp_min;
			dp_max[i][j] = temp_max;
		}
	}
	int ans_min = dp_min[1][n];
	int ans_max = dp_max[1][n];
	for (int i = 2; i <= n - 1; i++)
	{
		ans_min = min(ans_min, dp_min[i][i + n - 1]);
		ans_max = max(ans_max, dp_max[i][i + n - 1]);
	}
	printf("%d\n%d", ans_min, ans_max);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

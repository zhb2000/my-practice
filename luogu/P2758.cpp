#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
//std::ios_base::sync_with_stdio(false);
#define LOCAL
//#define DEBUG
//#define CONSOLE_PAUSE


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

const int maxn = 2000 + 5;
char sa[maxn];
char sb[maxn];
int dp_arr[maxn][maxn];

int dp(int i, int j)
{
	if (i == 0)
		return j;
	else if (j == 0)
		return i;
	else 
	{
		if (dp_arr[i][j] != -1)
			return dp_arr[i][j];
		int a = dp(i - 1, j - 1) + (sa[i] == sb[j] ? 0 : 1);
		int b = dp(i, j - 1) + 1;
		int c = dp(i - 1, j) + 1;
		dp_arr[i][j] = min(a, min(b, c));
		return dp_arr[i][j];
	}
}

void init()
{
	memset(dp_arr, -1, sizeof(dp_arr));
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	init();
	scanf("%s%s", sa + 1, sb+1);
	int n = strlen(sa + 1);
	int m = strlen(sb + 1);
	printf("%d", dp(n, m));

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

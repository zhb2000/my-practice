//P1439 【模板】最长公共子序列
//最长上升子序列、排列的性质
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

const int maxn = int(1e5 + 5);
int arr[maxn];
int d[maxn];
int p1[maxn], p2[maxn];
unordered_map<int, int> index_in_p2;

int lis(int n)
{
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

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &p1[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &p2[i]);

	for (int i = 1; i <= n; i++)
		index_in_p2[p2[i]] = i;
	for (int i = 1; i <= n; i++)
		arr[i] = index_in_p2[p1[i]];
	printf("%d", lis(n));

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
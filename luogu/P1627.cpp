//P1627 [CQOI2009]中位数
//数学、部分和
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
inline void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
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
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int maxn = int(1e5 + 5);
int arr[maxn];
unordered_map<int, int> right_counter;
unordered_map<int, int> left_counter;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, b;
	cin >> n >> b;
	int b_index;
	for (int i = 1; i <= n; i++)
	{
		int num;
		cin >> num;
		if (num > b)
			arr[i] = 1;
		else if (num == b)
		{
			arr[i] = 0;
			b_index = i;
		}
		else
			arr[i] = -1;
	}
	int sum = 0;
	for (int i = b_index; i <= n; i++)
	{
		sum += arr[i];
		if (right_counter.count(sum) == 0)
			right_counter[sum] = 0;
		right_counter[sum] += 1;
	}
	sum = 0;
	for (int i = b_index; i >= 1; i--)
	{
		sum += arr[i];
		if (left_counter.count(sum) == 0)
			left_counter[sum] = 0;
		left_counter[sum] += 1;
	}
	ll ans = 0;
	for (const auto &kv : right_counter)
	{
		int sum = kv.first;
		if (left_counter.count(-sum) == 0)
			continue;
		ans += ll(kv.second) * left_counter[-sum];
	}
	cout << ans;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

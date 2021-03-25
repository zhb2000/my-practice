//P1541 [NOIP2010 提高组] 乌龟棋
//刷表法，tuple+unordered_map
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

struct Entry
{
	int num[5];
	Entry(int one, int two, int three, int four)
	{
		num[1] = one; num[2] = two;
		num[3] = three; num[4] = four;
	}
	bool operator==(const Entry &other) const
	{
		for (int step = 1; step <= 4; step++)
			if (num[step] != other.num[step])
				return false;
		return true;
	}
};

namespace std
{
	template<>
	struct hash<Entry>
	{
		size_t operator()(const Entry &e) const
		{
			const int base = 42;
			const int base2 = base * base;
			const int base3 = base2 * base;
			return e.num[1] + e.num[2] * base + e.num[3] * base2 + e.num[4] * base3;
		}
	};
}

const int maxn = 350 + 5;
const int maxm = 120 + 5;
int a[maxn];
unordered_map<Entry, int> f[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int num_arr[] = { 0,0,0,0,0 };
	for (int c = 1; c <= m; c++)
	{
		int num;
		cin >> num;
		num_arr[num]++;
	}
	f[1][{num_arr[1], num_arr[2], num_arr[3], num_arr[4]}] = a[1];
	for (int i = 1; i <= n; i++)
	{
		for (const auto &kv : f[i])
		{
			const Entry &e = kv.first;
			int v = kv.second;
			for (int step = 1; step <= 4; step++)
			{
				if (e.num[step] > 0)
				{
					Entry new_e = e;
					new_e.num[step] -= 1;
					int nxt = i + step;
					assert(nxt <= n);
					if (f[nxt].count(new_e) == 0)
						f[nxt][new_e] = 0;
					f[nxt][new_e] = max(f[nxt][new_e], v + a[nxt]);
				}
			}
		}
	}
	assert(f[n].size() == 1);
	assert(f[n].count({ 0,0,0,0 }) == 1);
	cout << f[n][{0, 0, 0, 0}];


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

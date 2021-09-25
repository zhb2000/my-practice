#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LOCAL
#define DEBUG
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
#include<numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
template <class Int>
inline Int fast_read()
{
	Int x = 0, f = 1; char ch = char(getchar());
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = char(getchar()); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = char(getchar()); }
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
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l - 1 <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

bool can_pop_front(const deque<int> &q, int num)
{
	return !q.empty() && q.front() == num;
}

bool can_pop_back(const deque<int> &q, int num)
{
	return !q.empty() && q.back() == num;
}

bool check(const vector<int> &a1, const vector<int> &a2)
{
	deque<int> q;
	assert(a1.size() == a2.size());
	int n = int(a1.size());
	int i = 0, j = 0;
	while (i < n || j < n)
	{
		if (i < n)
		{
			q.push_back(a1[i]);
			i++;
		}
		assert(j < n);
		while (j < n && (can_pop_front(q, a2[j]) || can_pop_back(q, a2[j])))
		{
			if (can_pop_front(q, a2[j]))
				q.pop_front();
			else
				q.pop_back();
			j++;
		}
		if (i == n && j < n)
			return false;
	}
	assert(i == n);
	assert(j == n);
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	int n, k;
	cin >> n >> k;
	vector<int> push_arr;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		push_arr.push_back(num);
	}
	vector<int> pop_arr;
	for (int q = 1; q <= k; q++)
	{
		pop_arr.clear();
		for (int i = 0; i < n; i++)
		{
			int num;
			cin >> num;
			pop_arr.push_back(num);
		}
		if (check(push_arr, pop_arr))
			puts("yes");
		else
			puts("no");
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

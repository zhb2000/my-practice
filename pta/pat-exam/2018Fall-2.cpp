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
#include<ctime>
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
inline Int clen(Int l, Int r) { assert(l <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int maxg = int(1e6 + 3);
set<int> incomp[maxg];

bool check(const vector<int> &pack)
{
	int len = int(pack.size());
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			int a = pack[i];
			int b = pack[j];
			if (incomp[a].count(b) > 0)
				return false;
		}
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	//cout << "start" << endl;
	for (int c = 1; c <= n; c++)
	{
		int a, b;
		cin >> a >> b;
		incomp[a].insert(b);
		incomp[b].insert(a);
	}
	//cout << "20004 20003: " << incomp[20004].count(20003) << endl;
	vector<int> pack;
	for (int c = 1; c <= m; c++)
	{
		pack.clear();
		int k;
		cin >> k;
		for (int i = 0; i < k; i++)
		{
			int a;
			cin >> a;
			pack.push_back(a);
		}
		//cout << pack << endl;
		bool res = check(pack);
		if (res)
			cout << "Yes\n";
		else
			cout << "No\n";
	}



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

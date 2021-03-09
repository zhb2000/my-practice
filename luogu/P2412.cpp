//P2412 查单词
//ST 表
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
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int maxn = int(5e4 + 5);
const int logmax = 16;

string raw_words[maxn];
string words[maxn];
int log_2[maxn];
int f[maxn][logmax];

void calc_log2()
{
	log_2[1] = 0;
	for (int i = 2; i < maxn; i++)
		log_2[i] = log_2[i / 2] + 1;
}

void build(int n)
{
	for (int i = 1; i <= n; i++)
		f[i][0] = i;
	for (int j = 1; j < logmax; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			int index1 = f[i][j - 1];
			int index2 = f[i + (1 << (j - 1))][j - 1];
			string &s1 = words[index1];
			string &s2 = words[index2];
			f[i][j] = (s1 > s2) ? index1 : index2;
		}
	}
}

int query(int l, int r)
{
	int s = log_2[clen(l, r)];
	int index1 = f[l][s];
	int index2 = f[r - (1 << s) + 1][s];
	string &s1 = words[index1];
	string &s2 = words[index2];
	return (s1 > s2) ? index1 : index2;
}

string str_to_lower(const string &s)
{
	string ret;
	ret.reserve(s.length());
	for (char ch : s)
		ret.push_back(tolower(ch));
	return ret;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	calc_log2();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> raw_words[i];
		words[i] = str_to_lower(raw_words[i]);
	}
	build(n);
	for (int c = 1; c <= m; c++)
	{
		int l, r;
		cin >> l >> r;
		int index = query(l, r);
		cout << raw_words[index] << '\n';
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

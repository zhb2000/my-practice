//F - Meet in another world, enjoy tasty food!
//https://ac.nowcoder.com/acm/contest/15167/F
//模拟、暴力
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

const ll INF = ll(1e18 + 10);
const int maxn = 1000 + 10;
ll values[maxn];
ll ranks[maxn];
bool in_q[maxn];

ll div_ll(ll a, ll b)
{
	ll x = a / b;
	if (a == b * x)
		return x;
	return x + 1;
}

int find_want(int n)
{
	ll min_x = INF;
	int pos = -1;
	for (int i = 1; i <= n; i++)
	{
		if (!in_q[i])
			continue;
		ll x = div_ll(values[i], ranks[i]);
		if (x < min_x)
		{
			min_x = x;
			pos = i;
		}
	}
	assert(pos != -1);
	return pos;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> values[i];
		ranks[i] = i;
		in_q[i] = true;
	}
	vector<int> ans;
	int in_qnum = n;
	while (in_qnum > 0)
	{
		int p = find_want(n);
		ans.push_back(p);
		in_q[p] = false;
		in_qnum--;
		ll rnd = div_ll(values[p], ranks[p]);
		for (int i = 1; i < p; i++)
		{
			if (!in_q[i])
				continue;
			values[i] -= rnd * ranks[i];
		}
		int leave_num = 1;
		for (int i = p + 1; i <= n; i++)
		{
			if (!in_q[i])
				continue;
			values[i] -= (rnd - 1) * ranks[i];
			ranks[i] -= leave_num;
			values[i] -= ranks[i];
			if (values[i] <= 0)
			{
				leave_num++;
				in_q[i] = false;
				ans.push_back(i);
				in_qnum--;
			}
		}
	}

	bool isfirst = true;
	for (int x : ans)
	{
		if (isfirst)
			isfirst = false;
		else
			cout << " ";
		cout << x;
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

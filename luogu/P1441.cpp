//P1441 砝码称重
//DFS 子集枚举 + DP 0-1 背包
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

const int maxn = 20 + 3;
int arr[maxn];
int n, m;
vector<int> weights;
int ans = 0;

int solve_plan(const vector<int> &weights)
{
	int n = int(weights.size());
	unordered_set<int> ans_set = { 0 };
	for (int w : weights)
	{
		vector<int> new_weights;
		for (int acc : ans_set)
			new_weights.push_back(acc + w);
		ans_set.insert(new_weights.begin(), new_weights.end());
	}
	return int(ans_set.size()) - 1;
}

void dfs(int p, bool keep_p)
{
	int used = int(weights.size());
	if (used == n - m)
	{
		int temp_ans = solve_plan(weights);
		ans = max(ans, temp_ans);
		return;
	}
	if (p == n)
	{
		assert(int(weights.size()) < n - m);
		return;
	}
	if (used + (n - p) < n - m)
		return;
	if (keep_p)
		weights.push_back(arr[p]);
	dfs(p + 1, true);
	dfs(p + 1, false);
	if (keep_p)
		weights.pop_back();
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	dfs(0, true);
	dfs(0, false);

	cout << ans;



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

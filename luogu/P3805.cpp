//P3805 【模板】manacher算法
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

const int maxn = int(1.1e7 + 5);
int d1[maxn * 2];
char input[maxn];

void solve(const string &s)
{
	int n = int(s.length());
	for (int i = 0, l = 0, r = -1; i < n; i++)
	{
		int k;
		if (i > r)
			k = 1;
		else
			k = min(d1[l + r - i], clen(i, r));
		while (i - k >= 0 && i + k < n && s[i - k] == s[i + k])
			k++;
		d1[i] = k;
		if (i + k - 1 > r)
		{
			l = i - k + 1;
			r = i + k - 1;
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%s", input);
	string s;
	s.push_back('#');
	for (int i = 0; input[i] != '\0'; i++)
	{
		s.push_back(input[i]);
		s.push_back('#');
	}
	solve(s);
	int ans = 0;
	for (int i = 0; i<int(s.length()); i++)
		ans = max(ans, d1[i] - 1);
	printf("%d", ans);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
//P3375 【模板】KMP字符串匹配
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

void calc_nxt(const char *s, int len, int *nxt)
{
	nxt[0] = 0;
	for (int i = 1; i < len; i++)
	{
		int j = nxt[i - 1];
		while (j > 0 && s[i] != s[j])
			j = nxt[j - 1];
		if (s[i] == s[j])
			j += 1;
		nxt[i] = j;
	}
}

void kmp(const char *str, int slen, const char *pstr, int plen, int *nxt)
{
	calc_nxt(pstr, plen, nxt);
	int j = 0;
	for (int i = 0; i < slen; i++)
	{
		while (j > 0 && str[i] != pstr[j])
			j = nxt[j - 1];
		if (str[i] == pstr[j])
			j++;
		if (j == plen)
		{
			printf("%d\n", i - plen + 1 + 1);
			j = nxt[j - 1];
		}
	}
}

const int maxn = int(1e6 + 3);
int nxt[maxn];
char str[maxn];
char pstr[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%s", str);
	scanf("%s", pstr);
	int slen = int(strlen(str)), plen = int(strlen(pstr));
	kmp(str, slen, pstr, plen, nxt);
	bool isfirst = true;
	for (int i = 0; i < plen; i++)
	{
		if (isfirst)
			isfirst = false;
		else
			printf(" ");
		printf("%d", nxt[i]);
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
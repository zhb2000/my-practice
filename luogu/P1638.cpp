//P1638 逛画展
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
inline Int quick_read()
{
	Int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
inline int readint() { return quick_read<int>(); }
inline ll readll() { return quick_read<ll>(); }
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

const int maxn = 1000000 + 3;
const int maxm = 2000 + 3;
int arr[maxn];
int cnt[maxm];
int art_cnt;

inline void get_in(int i)
{
	int artist = arr[i];
	if (cnt[artist] == 0)
		art_cnt++;
	cnt[artist]++;
}

inline void get_out(int i)
{
	int artist = arr[i];
	cnt[artist]--;
	if (cnt[artist] == 0)
		art_cnt--;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	int ans = INTMAX;
	int a, b;
	art_cnt = 0;
	int i = 1, j = 1;
	get_in(i);
	while (i <= j && j <= n)
	{
		if (art_cnt >= m)
		{
			assert(art_cnt == m);
			int temp = clen(i, j);
			if (temp < ans )
			{
				ans = temp;
				a = i; b = j;
			}
			get_out(i);
			i++;
		}
		else//art_cnt < m
		{
			j++;
			if (j <= n)
				get_in(j);
			else
				break;
		}
	}
	printf("%d %d", a, b);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
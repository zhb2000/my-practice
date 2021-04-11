#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
//std::ios_base::sync_with_stdio(false);
#define LOCAL
//#define DEBUG
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

const int maxn = int(1e4 + 5);
const int maxnum = int(1e4 + 5);
int a_arr[maxn], b_arr[maxn], c_arr[maxn];
int lbound[maxn], rbound[maxn];
vector<int> rela1[maxn], rela2[maxn];

bool choose[maxn];
#ifdef DEBUG
int best_ans[maxn];
int temp_ans[maxn];
#endif // DEBUG
unordered_set<int> neqs[maxn];
ll max_happy = -1;

//use rela1
bool can_buy(int y)
{
	for (int x : rela1[y])
		if (!choose[x])
			return false;
	return true;
}

//use rela2
void calc_neq_buy(int y)
{
	for (int x : rela2[y])
	{
		if (!choose[x])
		{
			neqs[y].insert(lbound[x]);
			neqs[y].insert(rbound[x]);
		}
	}
}

//if ret==0, can't buy
int u_cur_buy(int y)
{
	assert(can_buy(y));
	int a = a_arr[y], b = b_arr[y], c = a_arr[y];
	int l = lbound[y], r = rbound[y];
	assert(a > 0);
	double mid = double(-b) / (2 * a);
	if (l > mid)
	{
		for (int num = r; num >= l; num--)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;//none can select
	}
	else if (r < mid)
	{
		for (int num = l; num <= r; num++)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;
	}
	else
	{
		int i = l, j = r;
		while (i <= j)
		{
			int far = abs(i - mid) > abs(j - mid) ? i : j;
			if (neqs[y].count(far) == 0)
				return far;
			if (far == i)
				i++;
			else
				j--;
		}
		return 0;
	}
}

int n_cur_buy(int y)
{
	assert(can_buy(y));
	int a = a_arr[y], b = b_arr[y], c = a_arr[y];
	int l = lbound[y], r = rbound[y];
	assert(a < 0);
	double mid = double(-b) / (2 * a);
	if (l > mid)
	{
		for (int num = l; num <= r; num++)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;//none can select
	}
	else if (r < mid)
	{
		for (int num = r; num >= l; num--)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;
	}
	else
	{
		int m = int(round(mid));
		for (int i = 0; l <= m - i || m + i <= r; i++)
		{
			if (l <= m - i && m + i <= r)
			{
				if (abs(m - i - mid) < abs(m + i - mid))
				{
					if (neqs[y].count(m - i) == 0)
						return m - i;
					else if (neqs[y].count(m + i) == 0)
						return m + i;
				}
				else
				{
					if (neqs[y].count(m + i) == 0)
						return m + i;
					else if (neqs[y].count(m - i) == 0)
						return m - i;
				}
			}
			else if (l <= m - i)//valid m-i, invalid m+i
			{
				if (neqs[y].count(m - i) == 0)
					return m - i;
			}
			else//valid m+i, invalid m-i
			{
				if (neqs[y].count(m + i) == 0)
					return m + i;
			}
		}
		return 0;
	}
}

int line_buy(int y)
{
	assert(can_buy(y));
	int a = a_arr[y], b = b_arr[y], c = a_arr[y];
	int l = lbound[y], r = rbound[y];
	assert(a == 0 && b != 0);
	if (b > 0)
	{
		for (int num = r; num >= l; num--)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;
	}
	else//b < 0
	{
		for (int num = l; num <= r; num++)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;
	}
}

//ret==0 means can't buy
int best_buy(int y)
{
	if (!can_buy(y))
		return 0;
	calc_neq_buy(y);
	int a = a_arr[y], b = b_arr[y];
	if (a > 0)
		return u_cur_buy(y);
	else if (a < 0)
		return n_cur_buy(y);
	else if (a == 0 && b != 0)
		return line_buy(y);
	else
	{
		int l = lbound[y], r = rbound[y];
		for (int num = l; num <= r; num++)
			if (neqs[y].count(num) == 0)
				return num;
		return 0;
	}
}

void generate_subset(int n, int cur)
{
	if (cur == n)
	{
		for (int y = 0; y < n; y++)
			neqs[y].clear();

		ll temp_happy = 0;
		for (int y = 0; y < n; y++)
		{
			if (choose[y])
			{
				int num = best_buy(y);
				if (num == 0)//can't buy any y, conflict
					return;
#ifdef DEBUG
				temp_ans[y] = num;
#endif // DEBUG
				ll a = a_arr[y], b = b_arr[y], c = c_arr[y];
				temp_happy += a * num * num + b * num + c;
			}
		}
		if (temp_happy > max_happy)
		{
			max_happy = temp_happy;
#ifdef DEBUG
			for (int y = 0; y < n; y++)
				best_ans[y] = temp_ans[y];
#endif // DEBUG
		}
		return;
	}

	choose[cur] = true;
	generate_subset(n, cur + 1);
	choose[cur] = false;
	generate_subset(n, cur + 1);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d%d%d", &lbound[i], &rbound[i], &a_arr[i], &b_arr[i], &c_arr[i]);
		assert(lbound[i] + 1 <= rbound[i] - 1);
	}
	for (int i = 0; i < m; i++)
	{
		int z, x, y;
		scanf("%d%d%d", &z, &x, &y);
		x -= 1; y -= 1;
		if (z == 1)
			rela1[y].push_back(x);
		else
			rela2[y].push_back(x);
	}

	if (n == 0)
		printf("0");
	else
	{
		generate_subset(n, 0);
		printf("%lld", max_happy);
#ifdef DEBUG
		printf("\n");
		for (int y = 0; y < n; y++)
			printf("%d ", best_ans[y]);
#endif // DEBUG

	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
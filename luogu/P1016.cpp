//P1016 [NOIP1999 提高组] 旅行家的预算
//贪心
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

vector<double> pos;
vector<double> price;
double d1, c, d2, p;
int n;

int cur = 0;
double fuel = 0.0;
double pay = 0.0;

//less or equal, return -1 if none
int next_better()
{
	double cur_price = price[cur];
	for (int i = cur + 1; i < int(price.size()); i++)
		if (price[i] <= cur_price)
			return i;
	return -1;
}

//return -1 if none
int best_within_full()
{
	double min_price = 1e9;
	int nxt = -1;
	for (int i = cur + 1; i < int(price.size()); i++)
	{
		if (pos[i] - pos[cur] >= c * d2)
			break;
		if (price[i] < min_price)
		{
			nxt = i;
			min_price = price[i];
		}
	}
	return nxt;
}

bool can_go_with_full(int i)
{
	double dist = pos[i] - pos[cur];
	return dist <= c * d2;
}

void add_to_full()
{
	pay += (c - fuel) * price[cur];
	fuel = c;
}

void go_and_consume(int nxt)
{
	fuel -= (pos[nxt] - pos[cur]) / d2;
	cur = nxt;
}

bool solve()
{
	assert(pos.size() == price.size());
	assert(int(pos.size()) == n + 2);

	int dest_pos = int(pos.size()) - 1;
	while (cur < dest_pos)
	{
		int better_pos = next_better();
		if (better_pos != -1 && can_go_with_full(better_pos))
		{
			//add enough to better
			double will_consume_fuel = (pos[better_pos] - pos[cur]) / d2;
			double fuel_to_add;
			if (will_consume_fuel > fuel)
				fuel_to_add = will_consume_fuel - fuel;
			else
				fuel_to_add = 0.0;
			pay += fuel_to_add * price[cur];
			fuel += fuel_to_add;
			go_and_consume(better_pos);
		}
		else
		{
			if (!can_go_with_full(cur + 1))
				return false;
			else
			{
				//add to full
				int nxt = best_within_full();
				assert(nxt != -1);
				add_to_full();
				go_and_consume(nxt);
			}
		}
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%lf%lf%lf%lf%d", &d1, &c, &d2, &p, &n);

	pos.push_back(0.0);
	price.push_back(p);
	for (int i = 1; i <= n; i++)
	{
		double di, pi;
		scanf("%lf%lf", &di, &pi);
		pos.push_back(di);
		price.push_back(pi);
	}
	pos.push_back(d1);
	price.push_back(0.0);

	if (solve())
		printf("%.2lf", pay);
	else
		printf("No Solution");



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

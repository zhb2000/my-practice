//L1-002 打印沙漏
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
const double EPS = 1e-7;
//------------------------ header end ------------------------

char read_char()
{
	while (true)
	{
		int ch = getchar();
		if (ch != '\r' && ch != '\n' && !isspace(ch))
			return ch;
	}
}

int get_floor_num(int n)
{
	double x = double(n);
	return int(floor(sqrt((x + 1) / 2)));
}

void print_char(char ch, int num)
{
	for (int ct = 1; ct <= num; ct++)
		printf("%c", ch);
}

void print_floor(int width, int max_width, char ch)
{
	int space = max_width - width;
	assert(iseven(space));
	print_char(' ', space / 2);
	print_char(ch, width);
	printf("\n");
}

void print(int floor_num, char ch)
{
	int max_width = 2 * floor_num - 1;
	for (int width = max_width; width >= 1; width -= 2)
		print_floor(width, max_width, ch);
	for (int width = 3; width <= max_width; width += 2)
		print_floor(width, max_width, ch);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	char ch;
	scanf("%d", &n);
	ch = read_char();
	int floor_num = get_floor_num(n);
	print(floor_num, ch);
	int used_num = 2 * floor_num * floor_num - 1;
	printf("%d\n", n - used_num);

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
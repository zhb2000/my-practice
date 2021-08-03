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

struct Node
{
	int num;
	int nxt;
};

const int maxn = int(1e5 + 3);
Node ns[maxn];

int list_len(int head)
{
	int len = 0;
	for (int p = head; p != -1; p = ns[p].nxt)
		len++;
	return len;
}

void print_list(int head)
{
	for (int p = head; p != -1; p = ns[p].nxt)
		cout << p << ' ' << ns[p].num << ' ' << ns[p].nxt << '\n';
}

void print_vec(const vector<int> &v)
{
	int n = int(v.size());
	for (int i = 0; i < n; i++)
	{
		int p = v[i];
		int num = ns[p].num;
		int nxt;
		if (i < n - 1)
			nxt = v[i + 1];
		else
			nxt = -1;
		if (nxt != -1)
			printf("%05d %d %05d\n", p, num, nxt);
		else
			printf("%05d %d %d\n", p, num, nxt);
	}
}

vector<int> list2vec(int head)
{
	assert(head != -1);
	vector<int> v;
	for (int p = head; p != -1; p = ns[p].nxt)
		v.push_back(p);
	return v;
}

// l1.len > l2.len
vector<int> merge2(int head1, int head2)
{
	vector<int> v1 = list2vec(head1);
	vector<int> v2 = list2vec(head2);
	assert(v1.size() >= v2.size() * 2);
	reverse(v2.begin(), v2.end());
	vector<int> v;
	int i = 0, j = 0;
	while (j < v2.size())
	{
		v.push_back(v1[i]); i++;
		v.push_back(v1[i]); i++;
		v.push_back(v2[j]); j++;
	}
	while (i < v1.size())
	{
		v.push_back(v1[i]); i++;
	}
	return v;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	//cpp_io();
	int ahead, bhead, all_n;
	cin >> ahead >> bhead >> all_n;
	for (int c = 1; c <= all_n; c++)
	{
		int i, num, nxt;
		cin >> i >> num >> nxt;
		ns[i].num = num; ns[i].nxt = nxt;
	}

	/*print_list(ahead);
	cout << endl;
	print_list(bhead);
	cout << endl;*/

	int alen = list_len(ahead);
	int blen = list_len(bhead);
	int head1, head2;
	if (alen > blen)
	{
		assert(alen >= 2 * blen);
		head1 = ahead;
		head2 = bhead;
	}
	else
	{
		assert(blen >= 2 * alen);
		head1 = bhead;
		head2 = ahead;
	}
	print_vec(merge2(head1, head2));


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

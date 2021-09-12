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

int fa[int(1e5) + 3];
bool exist[int(1e5) + 3];
unordered_map<int, int> ind_last;

//(indent, id)
Pii parse_line(const string &line)
{
	int indent = 0;
	int num = 0;
	for (char ch : line)
	{
		if (ch == ' ')
			indent++;
		else
		{
			assert(isdigit(ch));
			num = num * 10 + (ch - '0');
		}
	}
	return { indent, num };
}

void print_query(int qid)
{
	if (!exist[qid])
	{
		printf("Error: %d is not found.\n", qid);
		return;
	}
	vector<int> v;
	for (int p = qid; p != -1; p = fa[p])
		v.push_back(p);
	reverse(v.begin(), v.end());
	for (int i = 0; i < int(v.size()); i++)
	{
		if (i > 0)
			cout << "->";
		printf("%04d", v[i]);
	}
	cout << '\n';
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	//cpp_io();
	string n_str;
	getline(cin, n_str);
	int n = std::stoi(n_str);
	for (int c = 1; c <= n; c++)
	{
		string line;
		getline(cin, line);
		int indent, id;
		tie(indent, id) = parse_line(line);
		if (c == 1)
		{
			assert(indent == 0);
			assert(id == 0);
			fa[id] = -1;
			exist[id] = true;
			ind_last[indent] = id;
			continue;
		}
		assert(indent > 0);
		assert(ind_last.count(indent - 1) > 0);
		fa[id] = ind_last[indent - 1];
		exist[id] = true;
		ind_last[indent] = id;
	}
	int k;
	cin >> k;
	for (int c = 1; c <= k; c++)
	{
		int qid;
		cin >> qid;
		print_query(qid);
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

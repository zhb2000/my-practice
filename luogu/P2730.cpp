//P2730 [USACO3.2]魔板 Magic Squares
//BFS、康托展开
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

int fact[13];

struct Board
{
	int mat[2][4];
	const int &at(int x) const
	{
		int i = x / 4;
		int j = x % 4;
		if (i == 1)
			j = 3 - j;
		return mat[i][j];
	}
	int &at(int x)
	{
		int i = x / 4;
		int j = x % 4;
		if (i == 1)
			j = 3 - j;
		return mat[i][j];
	}
	int id() const
	{
		int sum = 0;
		for (int i = 0; i < 8; i++)
		{
			int lt = 0;
			for (int j = i + 1; j < 8; j++)
				if (at(j) < at(i))
					lt++;
			int after = clen(i + 1, 7);
			sum += lt * fact[after];
		}
		return sum + 1;
	}
	Board son(char op) const
	{
		Board s = Board(*this);
		s.update(op);
		return s;
	}
	void update(char op)
	{	
		if (op == 'A')
			update_a();
		else if (op == 'B')
			update_b();
		else
		{
			assert(op == 'C');
			update_c();
		}
	}
	void update_a()
	{
		int temp[4];
		memcpy(temp, mat[0], sizeof(int) * 4);
		memcpy(mat[0], mat[1], sizeof(int) * 4);
		memcpy(mat[1], temp, sizeof(int) * 4);
	}
	void update_b()
	{
		int right0 = mat[0][3], right1 = mat[1][3];
		for (int j = 2; j >= 0; j--)
		{
			mat[0][j + 1] = mat[0][j];
			mat[1][j + 1] = mat[1][j];
		}
		mat[0][0] = right0;
		mat[1][0] = right1;
	}
	void update_c()
	{
		int a = mat[0][1], b = mat[0][2];
		int c = mat[1][1], d = mat[1][2];
		mat[0][1] = c; mat[0][2] = a;
		mat[1][1] = d; mat[1][2] = b;
	}
};

ostream &operator<<(ostream &os, const Board &b)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << b.mat[i][j];
		cout << '\n';
	}
	return os;
}

const int maxfact = int(5e4);
int from[maxfact];
char last_op[maxfact];

int bfs(const Board &start, const Board &dest)
{
	queue<Board> q;
	int sid = start.id(), did = dest.id();
	from[sid] = -1; last_op[sid] = 1; q.push(start);
	while (!q.empty())
	{
		Board u = q.front(); q.pop();
		int uid = u.id();
		if (uid == did)
			return uid;
		for (char op = 'A'; op <= 'C'; op++)
		{
			Board v = u.son(op);
			int vid = v.id();
			if (last_op[vid] != 0)
				continue;
			from[vid] = uid;
			last_op[vid] = op;
			q.push(v);
		}
	}
	return -1;
}

void calc_fact(int n)
{
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = fact[i - 1] * i;
}

void init()
{
	calc_fact(10);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	init();
	Board start, dest;
	for (int i = 0; i < 8; i++)
	{
		int number;
		cin >> number;
		dest.at(i) = number;
		start.at(i) = i + 1;
	}
	int did = bfs(start, dest);
	assert(did != -1);
	assert(did == dest.id());
	vector<char> op_seq;
	for (int u = did; from[u] != -1; u = from[u])
		op_seq.push_back(last_op[u]);
	reverse(op_seq.begin(), op_seq.end());
	cout << op_seq.size() << '\n';
	int c = 0;
	for (char op : op_seq)
	{
		cout << op;
		c++;
		if (c == 60)
			cout << '\n';
	}

#ifdef DEBUG1
	cout << '\n';
	cout << start;
	for (char op : op_seq)
	{
		cout << op << '\n';
		start.update(op);
		cout << start;
	}
#endif // DEBUG

#ifdef DEBUG2
	cout << '\n';
	cout << dest;
	cout << '\n';
	cout << start;
	string test = "BCABCCB";
	for (char op : test)
	{
		cout << op << '\n';
		start.update(op);
		cout << start;
	}
#endif // DEBUG


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

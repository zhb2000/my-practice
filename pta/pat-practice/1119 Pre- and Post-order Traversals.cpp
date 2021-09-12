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

struct Node
{
	int val;
	int lch;
	int rch;
};

const int maxn = 100;
Node ns[maxn];
int node_cnt = 0;
int new_node() { return ++node_cnt; }
int preorder[maxn];
int postorder[maxn];

Pii lr_size(int prel, int prer, int postl, int postr)
{
	int lrootval = preorder[prel + 1];
	for (int i = postl; i <= postr; i++)
	{
		if (postorder[i] == lrootval)
		{
			int lsz = clen(postl, i);
			int rsz = clen(i + 1, postr - 1);
			return { lsz, rsz };
		}
	}
	assert(false);
	return { -1, -1 };
}

//(root, unique)
pair<int, bool> build_tree(int prel, int prer, int postl, int postr)
{
	assert(clen(prel, prer) == clen(postl, postr));
	if (prer < prel)
		return { -1, true };
	if (clen(prel, prer) == 1)
	{
		int root = new_node();
		ns[root].val = preorder[prel];
		ns[root].lch = ns[root].rch = -1;
		return { root, true };
	}
	assert(preorder[prel] == postorder[postr]);
	if (preorder[prel + 1] == postorder[postr - 1])//single side, no unique
	{
		int root = new_node();
		ns[root].val = preorder[prel];
		int lch; bool no_use;
		tie(lch, no_use) = build_tree(prel + 1, prer, postl, postr - 1);
		ns[root].lch = lch;
		ns[root].rch = -1;
		return { root, false };
	}
	else
	{
		int root = new_node();
		ns[root].val = preorder[prel];
		int lsz, rsz;
		tie(lsz, rsz) = lr_size(prel, prer, postl, postr);
		int lch, rch;
		bool lunique, runique;
		tie(lch, lunique) = build_tree(prel + 1, prel + 1 + lsz - 1, postl, postl + lsz - 1);
		tie(rch, runique) = build_tree(prel + 1 + lsz, prer, postl + lsz, postr - 1);
		ns[root].lch = lch;
		ns[root].rch = rch;
		return { root, lunique && runique };
	}
}

void inorder_print(int u, bool &isfirst)
{
	if (u == -1)
		return;
	inorder_print(ns[u].lch, isfirst);
	if (isfirst)
		isfirst = false;
	else
		cout << " ";
	cout << ns[u].val;
	inorder_print(ns[u].rch, isfirst);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	//cpp_io();
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> preorder[i];
	for (int i = 1; i <= n; i++)
		cin >> postorder[i];
	int root; bool unq;
	tie(root, unq) = build_tree(1, n, 1, n);
	cout << (unq ? "Yes" : "No") << '\n';
	bool isfirst = true;
	inorder_print(root, isfirst);
	cout << "\n";


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

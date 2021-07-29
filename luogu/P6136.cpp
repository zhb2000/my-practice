//P6136 【模板】普通平衡树（数据加强版）
//替罪羊树
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
	ll num;
	int cnt;
	int lch;
	int rch;
	int num_size;
	int tree_size;
	Node()
	{
		cnt = 1;
		lch = 0;
		rch = 0;
		num_size = 1;
		tree_size = 1;
	}
};

const double balance_alpha = 0.7;
const int maxn = int(1e6 + 1e5 + 5);
Node ns[maxn];
int nxt_new = 1;
int new_node() { return nxt_new++; }
vector<int> flat_vec;

int tree_size(int u)
{
	if (u != 0)
		assert(ns[u].tree_size == tree_size(ns[u].lch) + 1 + tree_size(ns[u].rch));
	return (u != 0) ? ns[u].tree_size : 0;
}

int num_size(int u)
{
	if (u != 0)
		assert(ns[u].num_size == num_size(ns[u].lch) + ns[u].cnt + num_size(ns[u].rch));
	return(u != 0) ? ns[u].num_size : 0;
}

//return: new root
int rebuild_from_vec(int l, int r)
{
	if (r < l)
		return 0;
	int m = avg2(l, r);
	int root = flat_vec[m];
	assert(root != 0);
	ns[root].lch = rebuild_from_vec(l, m - 1);
	ns[root].rch = rebuild_from_vec(m + 1, r);
	ns[root].num_size = num_size(ns[root].lch) + ns[root].cnt + num_size(ns[root].rch);
	ns[root].tree_size = tree_size(ns[root].lch) + 1 + tree_size(ns[root].rch);
	return root;
}

template<class Fn>
void inorder(int u, const Fn &f)
{
	if (u == 0)
		return;
	inorder(ns[u].lch, f);
	f(u);
	inorder(ns[u].rch, f);
}

void try_rebuild(int &u)
{
	assert(u != 0);
	int lts = tree_size(ns[u].lch);
	int rts = tree_size(ns[u].rch);
	assert(ns[u].tree_size == lts + 1 + rts);
	if (double(max(lts, rts)) / ns[u].tree_size > balance_alpha)
	{
		flat_vec.clear();
		inorder(u, [](int node)
		{
			if (node != 0 && ns[node].cnt > 0)
				flat_vec.push_back(node);
		});
		u = rebuild_from_vec(0, int(flat_vec.size()) - 1);
	}
}

//return: new root after rebuild
void u_insert(int &u, ll num)
{
	if (u == 0)
	{
		u = new_node();
		ns[u].num = num;
		return;
	}

	if (num == ns[u].num)
		ns[u].cnt++;
	else if (num < ns[u].num)
		u_insert(ns[u].lch, num);
	else
		u_insert(ns[u].rch, num);
	ns[u].num_size++;
	assert(ns[u].num_size == num_size(ns[u].lch) + ns[u].cnt + num_size(ns[u].rch));
	ns[u].tree_size = tree_size(ns[u].lch) + 1 + tree_size(ns[u].rch);
	try_rebuild(u);
}

void u_remove(int u, ll num)
{
	assert(u != 0);
	if (num == ns[u].num)
	{
		assert(ns[u].cnt > 0);
		ns[u].cnt--;
	}
	else if (num < ns[u].num)
	{
		assert(ns[u].lch != 0);
		u_remove(ns[u].lch, num);
	}
	else
	{
		assert(ns[u].rch != 0);
		u_remove(ns[u].rch, num);
	}
	ns[u].num_size--;
	assert(ns[u].num_size == num_size(ns[u].lch) + ns[u].cnt + num_size(ns[u].rch));
}

//Get k-th number
ll rank_k(int u, int k)
{
	assert(u != 0);
	assert(k >= 1);
	int lns = num_size(ns[u].lch);
	if (k <= lns)
		return rank_k(ns[u].lch, k);
	else if (lns < k && k <= lns + ns[u].cnt)
	{
		assert(ns[u].cnt > 0);
		return ns[u].num;
	}
	else
		return rank_k(ns[u].rch, k - lns - ns[u].cnt);
}

int rank_of_num(int u, ll num)
{
	assert(u != 0);
	int lns = num_size(ns[u].lch);
	if (num == ns[u].num)
	{
		assert(ns[u].cnt > 0);
		return lns + 1;
	}
	else if (num < ns[u].num)
		return rank_of_num(ns[u].lch, num);
	else
		return lns + ns[u].cnt + rank_of_num(ns[u].rch, num);
}

int u_find(int u, ll num)
{
	if (u == 0)
		return 0;
	if (num == ns[u].num)
		return (ns[u].cnt > 0) ? u : 0;
	else if (num < ns[u].num)
		return u_find(ns[u].lch, num);
	else
		return u_find(ns[u].rch, num);
}

int root = 0;

ll pre_num(ll num)
{
	assert(u_find(root, num) != 0);
	int k = rank_of_num(root, num) - 1;
	return rank_k(root, k);
}

ll post_num(ll num)
{
	int u = u_find(root, num);
	assert(u != 0);
	int k = rank_of_num(root, num) + ns[u].cnt;
	return rank_k(root, k);
}

void print_tree()
{
	auto f = [](int u)
	{
		if (u == 0)
			return;
		cout << ns[u].num << "[" << ns[u].cnt << "," << ns[u].num_size << "," << ns[u].tree_size << "] ";
	};
	inorder(root, f);
	cout << endl;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		ll num;
		cin >> num;
		u_insert(root, num);
	}

	ll last = 0;
	ll ans_xor = 0;
	for (int i = 1; i <= m; i++)
	{
		ll opt, x;
		cin >> opt >> x;
		x ^= last;

		/*cout << "------------------------------------------" << endl;
		cout << "i: " << i << ", opt: " << opt << ", x: " << x << '\n';*/

		if (opt == 1)
			u_insert(root, x);
		else if (opt == 2)
			u_remove(root, x);
		else if (opt == 3)
		{
			u_insert(root, x);
			ll ans = rank_of_num(root, x);
			last = ans; ans_xor ^= ans;
			u_remove(root, x);
		}
		else if (opt == 4)
		{
			ll ans = rank_k(root, int(x));
			last = ans; ans_xor ^= ans;
		}
		else if (opt == 5)
		{
			u_insert(root, x);
			ll ans =  pre_num(x);
			last = ans; ans_xor ^= ans;
			u_remove(root, x);
		}
		else
		{
			assert(opt == 6);
			u_insert(root, x);
			ll ans =  post_num(x);
			last = ans; ans_xor ^= ans;
			u_remove(root, x);
		}

		//print_tree();
	}
	cout << ans_xor;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

//P3919 【模板】可持久化数组（可持久化线段树/平衡树）
//离线做法
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
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class arrType>
inline arrType avg2(arrType a, arrType b) { return a + ((b - a) >> 1); }
const int nonep = -1;
const int INTMAX = ~(1 << 31);

const int maxnum = (int)1e6 + 5;
int arr[maxnum];
int n, m;

template<int maxN>
struct Graph
{
	//edge
	int u_e[maxN], v_e[maxN], nxt_e[maxN], loc_e[maxN], new_e[maxN];
	//question
	int askloc_q[maxN], ans_q[maxN], nxt_q[maxN];
	//node
	int qhead_n[maxN], ehead_n[maxN];

	int nei;
	int nni;
	int nqi;
	Graph() { reset(); }
	void reset()
	{
		nei = 0; nni = 1; nqi = 0;
		qhead_n[0] = nonep; ehead_n[0] = nonep;
	}
	int newnode() { qhead_n[nni] = nonep; ehead_n[nni] = nonep; return nni++; }
	int newedge() { return nei++; }
	int newquestion() { return nqi++; }
	//返回新结点的指针
	int add_version(int u, int loc, int newval)
	{
		int nd = newnode(); int e = newedge();
		u_e[e] = u;
		v_e[e] = nd;
		loc_e[e] = loc;
		new_e[e] = newval;
		nxt_e[e] = ehead_n[u];
		ehead_n[u] = e;
		return nd;
	}
	//返回新问题的指针
	int add_question(int u, int loc)
	{
		int q = newquestion();
		askloc_q[q] = loc;
		nxt_q[q] = qhead_n[u];
		qhead_n[u] = q;
		return q;
	}
	void dfs(int u)
	{
		//solve questions
		for (int q = qhead_n[u]; q != nonep; q = nxt_q[q])
		{
			int loc = askloc_q[q];
			ans_q[q] = arr[loc];
		}
		//recursive dfs
		for (int e = ehead_n[u]; e != nonep; e = nxt_e[e])
		{
			int loc = loc_e[e];
			int oldval = arr[loc];
			int newval = new_e[e];
			int v = v_e[e];
			arr[loc] = newval;//modify
#ifdef DEBUG
			printf("go: %d->%d, i: %d, val: %d->%d\n", u, v, loc, oldval, newval);
#endif // DEBUG
			dfs(v);
			arr[loc] = oldval;//restore
#ifdef DEBUG
			printf("back: %d->%d, i: %d, val: %d->%d\n", v, u, loc, newval, oldval);
#endif // DEBUG
		}
	}
	void dfs_print(int u)
	{
#ifdef DEBUG
		printf("node: %d\n", u);
		printf("arr: ");
		for (int i = 1; i <= n; i++)
			printf("%d ", arr[i]);
		printf("\n");
#endif // DEBUG

		//solve questions
		for (int q = qhead_n[u]; q != nonep; q = nxt_q[q])
		{
			int loc = askloc_q[q];
			ans_q[q] = arr[loc];
#ifdef DEBUG
			printf("a[%d]=%d; ", loc, arr[loc]);
#endif // DEBUG
		}
#ifdef DEBUG
		printf("\n----------\n");
#endif // DEBUG

		//recursive dfs
		for (int e = ehead_n[u]; e != nonep; e = nxt_e[e])
		{
			int loc = loc_e[e];
			int oldval = arr[loc];
			int newval = new_e[e];
			int v = v_e[e];
			arr[loc] = newval;//modify
			dfs_print(v);
			arr[loc] = oldval;//restore
		}
	}
};


int ver2node[maxnum];
Graph<maxnum> G;
vector<int> question_ptrs;

void print_ver()
{
	for (int c = 0; c <= m; c++)
	{
		printf("ver: %d, node: %d\n", c, ver2node[c]);
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif


	G.reset();
	ver2node[0] = 0;


	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	for (int c = 1; c <= m; c++)
	{
		int ver, op, loc;
		scanf("%d%d%d", &ver, &op, &loc);
		if (op == 1)
		{
			int newval;
			scanf("%d", &newval);
			int node = G.add_version(ver2node[ver], loc, newval);
			ver2node[c] = node;
		}
		else
		{
			int node = ver2node[ver];
			ver2node[c] = node;
			int q = G.add_question(node, loc);
			question_ptrs.push_back(q);
		}
	}
#ifdef DEBUG
	print_ver();
#endif // DEBUG

	G.dfs(0);
#ifdef DEBUG
	G.dfs_print(0);
#endif // DEBUG


	for (int q : question_ptrs)
	{
		printf("%d\n", G.ans_q[q]);
	}




#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
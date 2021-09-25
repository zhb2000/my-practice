#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>
#include<bitset>
#include<cctype>
#include<cstring>
#include<cassert>
using namespace std;
using ll = long long;
void cppio()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

const int maxnum = int(1e5 + 3);
int lch[maxnum];
int rch[maxnum];
int ht[maxnum];
int fa[maxnum];

void make_fa(int u, int father)
{
	if (u == -1)
		return;
	fa[u] = father;
	make_fa(lch[u], u);
	make_fa(rch[u], u);
}

int height(int u)
{
	if (u == -1)
		return 0;
	return 1 + max(height(lch[u]), height(rch[u]));
}

void init()
{
	memset(lch, -1, sizeof(lch));
	memset(rch, -1, sizeof(rch));
}

void make_node(int val)
{
	lch[val] = -1;
	rch[val] = -1;
	ht[val] = 0;
}

void rot1(int &u)
{
	int rm = rch[lch[u]];
	rch[lch[u]] = u;
	int new_u = lch[u];
	lch[u] = rm;
	u = new_u;
}

void rot4(int &u)
{
	int rm = lch[rch[u]];
	lch[rch[u]] = u;
	int new_u = rch[u];
	rch[u] = rm;
	u = new_u;
}

void rot2(int &u)
{
	int new_u = rch[lch[u]];
	int new_lch = lch[u];
	int rml = lch[new_u];
	int rmr = rch[new_u];
	rch[new_lch] = rml;
	lch[u] = rmr;
	rch[new_u] = u;
	lch[new_u] = new_lch;
	u = new_u;
}


void rot3(int &u)
{
	int new_u = lch[rch[u]];
	int new_rch = rch[u];
	int rmr = rch[new_u];
	int rml = lch[new_u];
	lch[new_rch] = rmr;
	rch[u] = rml;
	lch[new_u] = u;
	rch[new_u] = new_rch;
	u = new_u;
}

void do_balance(int &u)
{
	if (height(lch[u]) > height(rch[u]))
	{
		if (height(lch[lch[u]]) > height(rch[lch[u]]))
			rot1(u);
		else
			rot2(u);
	}
	else
	{
		assert(height(rch[u]) > height(lch[u]));
		if (height(rch[rch[u]]) > height(lch[rch[u]]))
			rot4(u);
		else
			rot3(u);
	}
}

void u_insert(int &u, int val)
{
	if (u == -1)
	{
		make_node(val);
		u = val;
		return;
	}
	if (val < u)
	{
		u_insert(lch[u], val);
	}
	else
	{
		assert(val > u);
		u_insert(rch[u], val);
	}
	//todo balance
	if (abs(height(lch[u]) - height(rch[u])) > 1)
	{
		do_balance(u);
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif // LOCAL

	int n;
	scanf("%d", &n);
	//init();
	int root = -1;
	for (int i = 0; i < n; i++)
	{
		int val;
		scanf("%d", &val);
		u_insert(root, val);
	}

	/*cout << root << endl;
	cout << lch[root] << endl;
	cout << rch[root] << endl;*/

	make_fa(root, -1);

	int m;
	scanf("%d", &m);
	for (int q = 1; q <= m; q++)
	{
		int a;
		cin >> a;
		string w;
		cin >> w;
		if (w == "and")//A and B are siblings
		{
			int b;
			cin >> b;
			cin >> w;
			cin >> w;

			//puts("Todo");

			if (a != b && fa[a] == fa[b])
				puts("Yes");
			else
				puts("No");
		}
		else
		{
			assert(w == "is");
			cin >> w;//the
			cin >> w;
			if (w == "root")//A is the root
			{
				if (root == a)
					puts("Yes");
				else
					puts("No");
			}
			else if (w == "parent")//A is the parent of B
			{
				cin >> w;//of;
				int b;
				cin >> b;
				if (lch[a] == b || rch[a] == b)
					puts("Yes");
				else
					puts("No");
			}
			else if (w == "left")//A is the left child of B
			{
				cin >> w;//child
				cin >> w;//of
				int b;
				cin >> b;
				if (lch[b] == a)
					puts("Yes");
				else
					puts("No");
			}
			else//A is the right child of B
			{
				assert(w == "right");
				cin >> w;//child
				cin >> w;//of
				int b;
				cin >> b;
				if (rch[b] == a)
					puts("Yes");
				else
					puts("No");
			}
		}
	}


	return 0;
}

// 12219 Common Subexpression Elimination
#define LOCAL

#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<tuple>
#include<utility>

using namespace std;

struct TreeNode
{
	string token;
	int hash;
	int lch;
	int rch;
};
typedef tuple<int, int, int> Group;

const int maxn = 50000 + 3;
TreeNode nodes[maxn];
int next_empty_node = 1;
char input_str[maxn * 8];
int glp;
map<Group, int> dict;//group to id
int vis[maxn * 8];
int kase;

int build_tree()
{
	int id = next_empty_node++;
	TreeNode& u = nodes[id];
	u.token.clear();
	u.hash = 0;
	while (isalpha(input_str[glp]))
	{
		u.token.push_back(input_str[glp]);
		u.hash <<= 5;
		u.hash += input_str[glp] - 'a' + 1;
		glp++;
	}
	if (input_str[glp] == '(')//u has two subtree
	{
		glp++;
		u.lch = build_tree();
		glp++;
		u.rch = build_tree();
		glp++;
	}
	else//u is a leaf
		u.lch = u.rch = 0;
	
	Group g(u.hash, u.lch, u.rch);
	if (dict.count(g) != 0)
	{
		next_empty_node--;
		return dict[g];
	}
	else
	{
		dict[g] = id;
		return id;
	}
}

void print_ans(int id)
{
	const TreeNode &u = nodes[id];
	vis[id] = kase;
	cout << u.token;

	if (u.lch == 0 && u.rch == 0)
		return;

	printf("(");
	if (vis[u.lch] != kase)
		print_ans(u.lch);
	else
		printf("%d", u.lch);
	printf(",");
	if (vis[u.rch] != kase)
		print_ans(u.rch);
	else
		printf("%d", u.rch);
	printf(")");
}

void init()
{
	next_empty_node = 1;
	glp = 0;
	dict.clear();
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	int c;
	cin >> c;
	for (kase = 1; kase <= c; kase++)
	{
		init();
		scanf("%s", input_str);
		int root_id = build_tree();
		print_ans(root_id);
		puts("");
	}
	return 0;
}
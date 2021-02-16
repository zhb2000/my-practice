// 八数码难题 A*

#define LOCAL

#include<cstring>
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cctype>
#include<map>
#include<algorithm>
#include<deque>
#include<queue>
#include<cctype>
#include<vector>
#include<stack>

using namespace std;

int dest[] = { 1,2,3,8,0,4,7,6,5 };
int delt_row[] = { -1,0,1,0 };
int delt_col[] = { 0,-1,0,1 };


int find_pos(int num, int *A)
{
	for (int i = 0; i < 9; i++)
		if (A[i] == num)
			return i;
	return -1;
}

struct NInfo
{
	int index;
	int f;
	int g;
	bool operator<(const NInfo &ptr2) const;
};

struct Node
{
	int matrix[9];
	int code;
	int f;
	int g;
	int h;
	//空格向上0、左1、下2、右3，若操作非法则返回false
	//行列编号从0开始
	bool move_op(int op)
	{
		int zero_pos = find_pos(0, this->matrix);
		int zero_row = zero_pos / 3;
		int zero_col = zero_pos % 3;
		if (zero_row == 0 && op == 0)
			return false;
		if (zero_row == 2 && op == 2)
			return false;
		if (zero_col == 0 && op == 1)
			return false;
		if (zero_col == 2 && op == 3)
			return false;
		int cell_row = zero_row + delt_row[op];
		int cell_col = zero_col + delt_col[op];
		int cell_pos = cell_row * 3 + cell_col;
		swap(this->matrix[zero_pos], this->matrix[cell_pos]);
		return true;
	}
	NInfo getNInfo()
	{
		NInfo pn;
		pn.index = code;
		pn.f = f;
		pn.g = g;
		return pn;
	}
};

const int maxn = (int)1e7;
int fact[9];
int vis[362880];//0未访问，1在open中，-1在closed中
Node nodes[maxn];
priority_queue<NInfo> open;

int calcu_h(const Node &node);
bool same_as_dest(const Node &node);
void read_matrix(int *A);
int encode_matrix(int *A);
void init_fact()
{
	fact[0] = 1;
	for (int i = 1; i < 9; i++)
		fact[i] = fact[i - 1] * i;
}




int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif // LOCAL

	init_fact();

	Node start_node;
	read_matrix(start_node.matrix);
	if (same_as_dest(start_node))
	{
		printf("0");
		return 0;
	}
	start_node.code = encode_matrix(start_node.matrix);
	start_node.g = 0;
	start_node.h = calcu_h(start_node);
	start_node.f = start_node.g + start_node.h;
	memcpy(&nodes[start_node.code], &start_node, sizeof(Node));
	vis[start_node.code] = 1;
	open.push(start_node.getNInfo());

	while (!open.empty())
	{
		Node &top_node = nodes[open.top().index]; open.pop();
		if (vis[top_node.code] == -1)
			continue;
		if (same_as_dest(top_node))
		{
			printf("%d", top_node.g);
			break;
		}
		vis[top_node.code] = -1;
		for (int op = 0; op < 4; op++)
		{
			Node new_node;
			memcpy(&new_node, &top_node, sizeof(Node));
			new_node.g += 1;
			if (!new_node.move_op(op))
				continue;
			new_node.code = encode_matrix(new_node.matrix);
			if (vis[new_node.code] == -1)
				continue;
			if (vis[new_node.code] == 1)
			{
				Node &node_in_open = nodes[new_node.code];
				if (new_node.g < node_in_open.g)
				{
					node_in_open.g = new_node.g;
					node_in_open.f = node_in_open.g + node_in_open.h;
					open.push(node_in_open.getNInfo());
					continue;
				}
			}
			new_node.h = calcu_h(new_node);
			new_node.f = new_node.g + new_node.h;
			memcpy(&nodes[new_node.code], &new_node, sizeof(Node));
			vis[new_node.code] = 1;
			open.push(new_node.getNInfo());
		}
	}
	return 0;
}

bool NInfo::operator<(const NInfo & n2) const
{
	/*Node &node1 = nodes[index];
	Node &node2 = nodes[ptr2.index];
	if (node1.f != node2.f)
		return node1.f > node2.f;
	else
		return node1.g < node2.g;*/
	if (this->f != n2.f)
		return this->f > n2.f;
	else
		return this->g < n2.g;
}

bool same_as_dest(const Node &node)
{
	for (int i = 0; i < 9; i++)
		if (node.matrix[i] != dest[i])
			return false;
	return true;
}

void read_matrix(int *A)
{
	char s[10];
	scanf("%s", s);
	for (int i = 0; i < 9; i++)
		A[i] = s[i] - '0';
}

int encode_matrix(int *A)
{
	int code = 0;
	for (int i = 0; i < 9; i++)
	{
		int cnt = 0;
		for (int j = i + 1; j < 9; j++)
		{
			if (A[j] < A[i])
				cnt++;
		}
		code += fact[8 - i] * cnt;
	}
	return code;
}

int calcu_h(const Node & node)
{
	int cnt = 0;
	for (int i = 0; i < 9; i++)
	{
		if (node.matrix[i] != dest[i])
			cnt++;
	}
	return cnt;
}
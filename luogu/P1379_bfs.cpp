// 八数码难题 bfs

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

struct Node
{
	int matrix[9];
	int route;
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
};

const int maxn = (int)1e7;
Node q[maxn];
int fact[9];
int vis[362880];
int rear;
int front;

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
	memset(vis, 0, sizeof(vis));
	front = rear = 0;
	read_matrix(q[rear].matrix);
	q[rear].route = 0;
	vis[encode_matrix(q[rear].matrix)] = 1;
	rear++;
	while (front != rear)
	{
		Node &front_node = q[front];
		if (same_as_dest(front_node))
		{
			printf("%d", front_node.route);
			break;
		}
		for (int op = 0; op < 4; op++)
		{
			Node &new_node = q[rear];
			memcpy(&new_node, &front_node, sizeof(Node));
			if (!new_node.move_op(op))
				continue;
			int code = encode_matrix(new_node.matrix);
			if (vis[code])
				continue;
			vis[code] = 1;
			new_node.route += 1;
			rear++;
		}
		front++;
	}
	
	return 0;
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
	for (int i = 0; i < 9; i++)
	{
		char ch = getchar();
		A[i] = ch - '0';
	}
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
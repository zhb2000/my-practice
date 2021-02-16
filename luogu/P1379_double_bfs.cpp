// 八数码难题 双向bfs

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
	int code;
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
Node rev_q[maxn];
int fact[9];
int vis[362880];
int pos_in_queue[362880];
int front, rear;
int rev_front, rev_rear;

void read_matrix(int *A);
int encode_matrix(int *A);

bool bfs();
bool rev_bfs();


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
	front = rear = 0;
	rev_front = rev_rear = 0;
	
	Node &start_node = q[rear];
	read_matrix(start_node.matrix);
	start_node.route = 0;
	start_node.code = encode_matrix(start_node.matrix);
	vis[start_node.code] = 1;
	pos_in_queue[start_node.code] = rear;
	rear++;

	Node &dest_node = rev_q[rev_rear];
	memcpy(dest_node.matrix, dest, sizeof(dest));
	dest_node.route = 0;
	dest_node.code = encode_matrix(rev_q[rev_rear].matrix);
	if (vis[dest_node.code] == 1)
	{
		printf("0");
		return 0;
	}
	vis[dest_node.code] = -1;
	pos_in_queue[dest_node.code] = rev_rear;
	rev_rear++;

	while (front != rear && rev_front != rev_rear)
	{
		if (bfs())
			break;
		if (rev_bfs())
			break;
	}
	
	return 0;
}

bool bfs()
{
	Node &front_node = q[front];
	if (vis[front_node.code] == -1)
	{
		Node &meet_node = rev_q[pos_in_queue[front_node.code]];
		int all_route = front_node.route + meet_node.route;
		printf("%d", all_route);
		return true;
	}
	for (int op = 0; op < 4; op++)
	{
		Node &new_node = q[rear];
		memcpy(&new_node, &front_node, sizeof(Node));
		if (!new_node.move_op(op))
			continue;
		new_node.code = encode_matrix(new_node.matrix);
		if (vis[new_node.code] == 1)
			continue;
		vis[new_node.code] = 1;
		new_node.route += 1;
		pos_in_queue[new_node.code] = rear;
		rear++;
	}
	front++;
	return false;
}

bool rev_bfs()
{
	Node &front_node = rev_q[rev_front];
	if (vis[front_node.code] == 1)
	{
		Node &meet_node = q[pos_in_queue[front_node.code]];
		int all_route = front_node.route + meet_node.route;
		printf("%d", all_route);
		return true;
	}
	for (int op = 0; op < 4; op++)
	{
		Node &new_node = rev_q[rev_rear];
		memcpy(&new_node, &front_node, sizeof(Node));
		if (!new_node.move_op(op))
			continue;
		new_node.code = encode_matrix(new_node.matrix);
		if (vis[new_node.code] == -1)
			continue;
		vis[new_node.code] = -1;
		new_node.route += 1;
		pos_in_queue[new_node.code] = rev_rear;
		rev_rear++;
	}
	rev_front++;
	return false;
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
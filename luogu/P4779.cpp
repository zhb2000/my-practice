//P4779 【模板】单源最短路径（标准版）
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
#include<unordered_map>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }

const int maxn = (int)1e5 + 5;
const int maxm = 2 * (int)1e5 + 5;
const int INF = ~(1 << 31);
const int nonep = -1;
int n, m, s;

struct HeapNode
{
	int u;
	int d;
	HeapNode(int u, int d)
		:u(u), d(d) {}
	HeapNode() = default;
	bool operator<(const HeapNode& hnode) const
	{
		return this->d > hnode.d;
	}
};
struct Graph
{
	int u_e[maxm], v_e[maxm], w_e[maxm], nxt_e[maxm];
	int d_nd[maxn], head_nd[maxn];
	//int parent_nd[maxn];
	bool known_nd[maxn];
	int nei;
	void reset()
	{
		nei = 0;
		fill_n(d_nd + 1, n, INF);
		memset(known_nd, 0, sizeof(known_nd));
		memset(head_nd, -1, sizeof(head_nd));
	}
	void add_edge(int from, int to, int w)
	{
		u_e[nei] = from; v_e[nei] = to; w_e[nei] = w;
		nxt_e[nei] = head_nd[from];
		head_nd[from] = nei;
		nei++;
	}
};
Graph G;


void dijkstra(int start)
{
	priority_queue<HeapNode> pq;
	G.d_nd[start] = 0;
	//G.parent_nd[start] = nonep;
	pq.push(HeapNode(start, 0));
	while (!pq.empty())
	{
		HeapNode hnode = pq.top(); pq.pop();
		int u = hnode.u; int d = hnode.d;
		if (G.known_nd[u])
			continue;
		G.known_nd[u] = true;
		G.d_nd[u] = d;
		for (int e = G.head_nd[u]; e != nonep; e = G.nxt_e[e])
		{
			int v = G.v_e[e];
			if (G.known_nd[v])
				continue;
			if (d < INF 
				&& d + G.w_e[e] < G.d_nd[v])
			{
				int oldd = G.d_nd[v];
				G.d_nd[v] = d + G.w_e[e];
				//G.parent_nd[v] = u;
				pq.push(HeapNode(v, G.d_nd[v]));
#ifdef DEBUG
				printf("use u: %d, update v: %d, d: %d -> %d\n", u, v, oldd, G.d_nd[v]);
#endif // DEBUG

			}
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%d%d%d", &n, &m, &s);
	G.reset();
	for (int c = 1; c <= m; c++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G.add_edge(u, v, w);
	}
	dijkstra(s);
	bool isfirst = true;
	for (int u = 1; u <= n; u++)
	{
		if (isfirst)
			isfirst = false;
		else
			printf(" ");
		printf("%d", G.d_nd[u]);
	}
		


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
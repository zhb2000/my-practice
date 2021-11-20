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
#include<set>
#include<stack>
#include<queue>
#include<deque>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<tuple>
#include<cassert>
#include<cctype>
#include<cmath>
#include<numeric>
using namespace std;
typedef long long ll; typedef unsigned long long ull; typedef unsigned int uint;
typedef pair<int, int> Pii;
template<class T, class Hasher = hash<T>, class Eq = equal_to<T>, class A = allocator<T>>
using uset = unordered_set<T, Hasher, Eq, A>;
template<class K, class V, class Hasher = hash<K>, class Eq = equal_to<K>, class A = allocator<K>>
using umap = unordered_map<K, V, Hasher, Eq, A>;
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
template<class Container>
ostream &output_sequence(ostream &os, const Container &container, const char *l, const char *r);
template<class T, class A>
ostream &operator<<(ostream &os, const vector<T, A> &v) { return output_sequence(os, v, "[", "]"); }
template<class T, class Cmp, class A>
ostream &operator<<(ostream &os, const set<T, Cmp, A> &s) { return output_sequence(os, s, "{", "}"); }
template<class T, class Hasher, class Eq, class A>
ostream &operator<<(ostream &os, const uset<T, Hasher, Eq, A> &s) { return output_sequence(os, s, "{", "}"); }
template<class Container>
ostream &output_sequence(ostream &os, const Container &container, const char *l, const char *r)
{
	os << l; bool isfirst = true;
	for (const auto &x : container) { if (isfirst) isfirst = false; else os << ", "; os << x; }
	os << r; return os;
}
template<class Map>
ostream &output_map(ostream &os, const Map &m);
template<class K, class V, class Cmp, class A>
ostream &operator<<(ostream &os, const map<K, V, Cmp, A> &m) { return output_map(os, m); }
template<class K, class V, class Hasher, class Eq, class A>
ostream &operator<<(ostream &os, const umap<K, V, Hasher, Eq, A> &m) { return output_map(os, m); }
template<class Map>
ostream &output_map(ostream &os, const Map &m)
{
	os << "{"; bool isfirst = true;
	for (const auto &kv : m)
	{
		if (isfirst) isfirst = false; else os << ", ";
		os << kv.first << ": " << kv.second;
	}
	os << "}"; return os;
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
const double EPS = 1e-7;
//------------------------ header end ------------------------

struct Neural
{
	double v, u, a, b, c, d;
	bool active;
	double input;
	int active_cnt = 0;
	//update v, u, active
	void update(double delta_t)
	{
		double vk = v + delta_t * (0.04 * v * v + 5 * v + 140 - u) + input;
		double uk = u + delta_t * a * (b * v - u);
		v = vk; u = uk;
		update_active();
	}
	void update_active()
	{
		if (v >= 30)
		{
			active = true;
			v = c; u += d;
		}
		else
			active = false;
		if (active)
			active_cnt += 1;
	}
};

struct Source
{
	int r;
	bool active;
	//update active
	void update(int rnd) { active = r > rnd; }
};

struct Edge
{
	int from, to; double w; int d;
	queue<int> timeout;
};

const int maxn = int(1e3 + 5), maxs = int(1e3 + 5), maxp = int(1e3 + 5);
Neural neurals[maxn];
Source sources[maxn + maxp];
//Edge edges[maxs];
vector<Edge> edges;
int N, S, P, T;

/* RAND_MAX assumed to be 32767 */
inline int myrand()
{
	static unsigned long next = 1;
	next = next * 1103515245 + 12345;
	return((unsigned)(next / 65536) % 32768);
}

inline void edge_recv(int ei, int cur_step)
{
	Edge &e = edges[ei];
	bool active;
	if (e.from < N)
		active = neurals[e.from].active;
	else
		active = sources[e.from].active;
	if (active)
		e.timeout.push(cur_step + e.d);
}

inline void edge_send(int ei, int cur_step)
{
	Edge &e = edges[ei];
	if (!e.timeout.empty() && e.timeout.front() <= cur_step)
	{
		assert(e.timeout.front() == cur_step);
		e.timeout.pop();
		assert(e.to < N);
		neurals[e.to].input += e.w;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	scanf("%d%d%d%d", &N, &S, &P, &T);
	double delta_t;
	scanf("%lf", &delta_t);
	for (int cnt = 0; cnt < N;)//neural
	{
		int rn; double v, u, a, b, c, d;
		scanf("%d%lf%lf%lf%lf%lf%lf", &rn, &v, &u, &a, &b, &c, &d);
		for (int i = cnt; i < cnt + rn; i++)
		{
			neurals[i].v = v; neurals[i].u = u;
			neurals[i].a = a; neurals[i].b = b;
			neurals[i].c = c; neurals[i].d = d;
			neurals[i].input = 0.0; neurals[i].active = false;
		}
		cnt += rn;
	}
	for (int i = N; i < N + P; i++)//source
	{
		scanf("%d", &sources[i].r);
		sources[i].active = false;
	}
	edges.reserve(S);
	for (int i = 0; i < S; i++)//edge
	{
		int s, t; double w; int d;
		scanf("%d%d%lf%d", &s, &t, &w, &d);
		Edge e;
		e.from = s; e.to = t; e.w = w; e.d = d;
		edges.push_back(std::move(e));
	}

	//update nn active?
	for (int i = 0; i < N; i++)
		neurals[i].update_active();

	for (int step = 1; step <= T; step++)
	{
		for (int i = 0; i < N; i++)
			neurals[i].input = 0.0;
		for (int i = 0; i < S; i++)
			edge_send(i, step);
		for (int i = 0; i < N; i++)
			neurals[i].update(delta_t);
		for (int i = N; i < N + P; i++)
			sources[i].update(myrand());
		for (int i = 0; i < S; i++)
			edge_recv(i, step);
		/*printf("step %d, nn.input: %.3lf, nn.v: %.3lf\n", step, neurals[0].input, neurals[0].v);
		printf("step %d, src.active: %d\n", step, int(sources[1].active));
		printf("\n");*/
	}

	double v_min, v_max; v_min = v_max = neurals[0].v;
	int cnt_min, cnt_max; cnt_min = cnt_max = neurals[0].active_cnt;
	for (int i = 1; i < N; i++)
	{
		const Neural &u = neurals[i];
		v_min = min(v_min, u.v);
		v_max = max(v_max, u.v);
		cnt_min = min(cnt_min, u.active_cnt);
		cnt_max = max(cnt_max, u.active_cnt);
	}
	printf("%.3lf %.3lf\n", v_min, v_max);
	printf("%d %d", cnt_min, cnt_max);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

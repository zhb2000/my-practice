//P1525 关押罪犯
//种类并查集
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
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
template <class T>
inline bool isodd(T num) { return (num & 1) != 0; }
template <class T>
inline bool iseven(T num) { return (num & 1) == 0; }
template <class T>
inline T clen(T l, T r) { return r - l + 1; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;

struct Edge
{
	int u, v, w;
	bool operator<(const Edge &other) const { return w > other.w; }
};

template <int maxNum>
class UnionFindSet
{
private:
    int fa_[maxNum];
    int size_[maxNum];
    int find(int x)
    {
        if (x != fa_[x])
            fa_[x] = find(fa_[x]);
        return fa_[x];
    }

public:
    void reset(int topn)
    {
        for (int x = 0; x <= topn; x++)
        {
            fa_[x] = x;
            size_[x] = 1;
        }
    }
    void union2(int x, int y)
    {
        int xx = find(x);
        int yy = find(y);
        if (xx == yy)
            return;
        if (size_[xx] < size_[yy])
            swap(xx, yy);
        fa_[yy] = xx;
        size_[xx] += size_[yy];
    }
    bool in_same(int x, int y)
    {
        return find(x) == find(y);
    }
};

const int maxn = 20000 + 5;
UnionFindSet<maxn * 2> uf;
vector<Edge> edges;
int n, m;

inline int in_different(int u) { return u + n; }

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%d%d", &n, &m);
    uf.reset(n * 2);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges.push_back({ u,v,w });
    }
    sort(edges.begin(), edges.end());
    bool isconflict = false;
    for (const auto &e : edges)
    {
        int u = e.u, v = e.v, w = e.w;
        if (uf.in_same(u, v))
        {
            isconflict = true;
            printf("%d", w);
            break;
        }
        else
        {
            uf.union2(u, in_different(v));
            uf.union2(v, in_different(u));
        }
    }
    if (!isconflict)
        printf("0");


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
//P1742 最小圆覆盖
//随机增量算法
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
inline Int avg2(Int a, Int b) { if (a > b) swap(a, b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { if (l > r) swap(l, r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

struct Vec
{
	double x, y;
	Vec() = default;
	Vec(double x, double y) :x(x), y(y) {}
	double len2() const { return x * x + y * y; }
	double len() const { return sqrt(len2()); }
	Vec operator+(const Vec &b) const { return Vec(x + b.x, y + b.y); }
	Vec operator-(const Vec &b) const { return Vec(x - b.x, y - b.y); }
	Vec operator*(double t) const { return Vec(x * t, y * t); }
	Vec operator/(double t) const { return Vec(x / t, y / t); }
	Vec operator-() const { return Vec(-x, -y); }
	Vec norm() const { return(*this) / len(); }
	Vec rot90() const { return Vec(y, -x); }
};

double dot(const Vec &a, const Vec &b) { return a.x * b.x + a.y * b.y; }
double cross(const Vec &a, const Vec &b) { return a.x * b.y - b.x * a.y; }
double dist(const Vec &a, const Vec &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

struct Circle
{
	Vec o;
	double r;
	Circle() = default;
	Circle(const Vec &o, double r) :o(o), r(r) {}
	bool contains(const Vec &p) const { return dist(o, p) <= r; }
};

Circle make_circle(const Vec &a, const Vec &b)
{
	double d = dist(a, b);
	Vec o = (a + b) / 2.0;
	return Circle(o, d / 2.0);
}

Vec intersetion(const Vec &p1, const Vec &v1, const Vec &p2, const Vec &v2)
{
	double t = cross((-p1 + p2), v2) / cross(v1, v2);
	return p1 + v1 * t;
}

Circle make_circle(const Vec &a, const Vec &b, const Vec &c)
{
	Vec p1 = (a + b) / 2.0;
	Vec v1 = (a - b).rot90();
	Vec p2 = (a + c) / 2.0;
	Vec v2 = (a - c).rot90();
	Vec o = intersetion(p1, v1, p2, v2);
	double r = dist(o, a);
	return Circle(o, r);
}

const int maxn = 100000 + 3;
Vec points[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &(points[i].x), &(points[i].y));
	random_shuffle(points + 1, points + 1 + n);
	auto circle = Circle({ 0.0, 0.0 }, 0.0);
	for (int i = 1; i <= n; i++)
	{
		if (circle.contains(points[i]))
			continue;
		circle = Circle(points[i], 0.0);
		for (int j = 1; j <= i - 1; j++)
		{
			if (circle.contains(points[j]))
				continue;
			circle = make_circle(points[i], points[j]);
			for (int k = 1; k <= j - 1; k++)
			{
				if (circle.contains(points[k]))
					continue;
				circle = make_circle(points[i], points[j], points[k]);
			}
		}
	}
	printf("%.10lf\n", circle.r);
	printf("%.10lf %.10lf", circle.o.x, circle.o.y);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

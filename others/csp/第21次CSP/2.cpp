//排序、前缀和
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
#define foreach(x, seq) for (const auto &x : seq)
const int INTMAX = ~(1 << 31);
const double EPS = 1e-8;
inline int sgn(double x) { if (x < -EPS) return -1; if (x > EPS) return 1; return 0; }
//------------------------ header end ------------------------

struct Student
{
	int y, result;
	bool operator<(const Student &other) const { return y < other.y; }
};

struct Entry
{
	int y;
	int num;
	int one_num;
};

const int maxn = int(1e5) + 5;
vector<Student> students;
vector<Entry> entries;
//[1, i]
int left_one[maxn], left_num[maxn];
//[i, n]
int right_one[maxn], right_num[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int y, result;
		cin >> y >> result;
		students.push_back(Student{y, result});
	}
	sort(students.begin(), students.end());
	entries.push_back(Entry{-1, -1, -1}); //entries[0], useless
	Entry entry{students[0].y, 0, 0};
	for (int i = 0; i < m; i++)
	{
		const Student &stu = students[i];
		if (stu.y > entry.y)
		{
			entries.push_back(entry);
			entry = Entry{stu.y, 0, 0};
		}
		entry.num += 1;
		entry.one_num += stu.result;
	}
	entries.push_back(entry);
	int n = int(entries.size()) - 1;

	for (int i = 1; i <= n; i++)
	{
		left_num[i] = left_num[i - 1] + entries[i].num;
		left_one[i] = left_one[i - 1] + entries[i].one_num;
	}
	for (int i = n; i >= 1; i--)
	{
		right_num[i] = right_num[i + 1] + entries[i].num;
		right_one[i] = right_one[i + 1] + entries[i].one_num;
	}
	int theta = entries[1].y;
	int correct_max = 0;
	for (int i = 1; i <= n; i++)
	{
		//zero num in [1, i-1]
		int left_correct = left_num[i - 1] - left_one[i - 1];
		//one num of i
		int mid_correct = entries[i].one_num;
		//one num in [i+1, n]
		int right_correct = right_one[i + 1];
		int correct = left_correct + mid_correct + right_correct;
		if (correct >= correct_max)
		{
			theta = entries[i].y;
			correct_max = correct;
		}
	}
	cout << theta;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

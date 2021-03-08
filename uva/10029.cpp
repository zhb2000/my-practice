//10029 Edit Step Ladders
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

const int maxn = int(25000 + 5);
string word_arr[maxn];
unordered_map<string, int> word_dict;
vector<int> G[maxn];
int step_arr[maxn];

string change_letter(const string &s, int i, char ch)
{
	string ret = s;
	ret[i] = ch;
	return ret;
}

string remove_letter(const string &s, int i)
{
	string ret;
	int len = int(s.length());
	ret.reserve(len - 1);
	for (int j = 0; j < len; j++)
		if (j != i)
			ret.push_back(s[j]);
	return ret;
}


//insert ch before index i
string insert_letter(const string &s, int i, char ch)
{
	string ret;
	int len = int(s.length());
	ret.reserve(len + 1);
	if (i == len)
	{
		ret = s;
		ret.push_back(ch);
		return ret;
	}

	for (int j = 0; j < len; j++)
	{
		if (j == i)
			ret.push_back(ch);
		ret.push_back(s[j]);
	}
	return ret;
}

void add_edge(int u, int v)
{
	G[u].push_back(v);
}

int longest_step(int u)
{
	if (step_arr[u] > 0)
		return step_arr[u];
	int max_son_step = 0;
	for (int v : G[u])
		max_son_step = max(max_son_step, longest_step(v));
	step_arr[u] = max_son_step + 1;
	return step_arr[u];
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	string word;
	int index = 1;
	while (cin >> word)
	{
		word_arr[index] = word;
		word_dict[word] = index;
		index++;
	}
	int n = index - 1;

	for (int u = 1; u <= n; u++)
	{
		const string &cur = word_arr[u];
		int len = int(cur.length());
		//change letter
		for (int i = 0; i < len; i++)
		{
			for (char ch = cur[i] + 1; ch <= 'z'; ch++)
			{
				string gen = change_letter(cur, i, ch);
				if (word_dict.count(gen) > 0)
				{
					int v = word_dict[gen];
					assert(u < v);
					add_edge(u, v);
				}
			}
		}
		//remove letter
		for (int i = 0; i < len; i++)
		{
			string gen = remove_letter(cur, i);
			if (word_dict.count(gen) > 0)
			{
				int v = word_dict[gen];
				if (u < v)
					add_edge(u, v);
			}
		}
		//insert letter
		for (int i = 0; i <= len; i++)
		{
			for (char ch = 'a'; ch <= 'z'; ch++)
			{
				string gen = insert_letter(cur, i, ch);
				if (word_dict.count(gen) > 0)
				{
					int v = word_dict[gen];
					if (u < v)
						add_edge(u, v);
				}
			}
		}
	}

	int ans = 0;
	for (int u = 1; u <= n; u++)
		ans = max(ans, longest_step(u));
	cout << ans << '\n';


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

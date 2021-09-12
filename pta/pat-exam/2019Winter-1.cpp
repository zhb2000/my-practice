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
	Int x = 0, f = 1; char ch = char(getchar());
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = char(getchar()); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = char(getchar()); }
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
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l - 1 <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

vector<string> repr[26 + 3];

void input_repr(int a)
{
	string line;
	for (int li = 0; li < 7; li++)
	{
		getline(cin, line);
		repr[a].push_back(line);
	}
}

vector<string> split_text(const string &text)
{
	vector<string> vec;
	string s;
	for (char ch : text)
	{
		if (isupper(ch))
		{
			s.push_back(ch);
		}
		else
		{
			if (!s.empty())
				vec.push_back(s);
			s.clear();
		}
	}
	if (!s.empty())
		vec.push_back(s);
	return vec;
}

void print_word(const string &word)
{
	for (int li = 0; li < 7; li++)
	{
		bool first_alpha = true;
		for (char ch : word)
		{
			if (first_alpha)
				first_alpha = false;
			else
				cout << " ";
			//cout << "test" << endl;
			cout << repr[ch - 'A'][li];
		}
		cout << "\n";
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	for (int a = 0; a < 26; a++)
	{
		input_repr(a);
	}
	string text;
	getline(cin, text);

	vector<string> words = split_text(text);
	//cout << words << endl;
	bool isfirst = true;
	for (const string &word : words)
	{
		if (isfirst)
			isfirst = false;
		else
			cout << "\n";
		print_word(word);
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

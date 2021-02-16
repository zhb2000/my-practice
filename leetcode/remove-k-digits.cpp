//移掉K位数字
//贪心、单调栈
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
const double EPS = 1e-7;
//------------------------ header end ------------------------

struct Entry
{
	char digit;
	int rest;
};

class Solution
{
public:
	string removeKdigits(string num, int k)
	{
		return remove_zero(solve(num, k));
	}

	string solve(const string &num, int k)
	{
		int n = int(num.length());
		int m = n - k;
		if (m == 0)
			return "0";
		stack<Entry> st;
		for (int i = 0; i < n; i++)
		{
			char digit = num[i];
			int cur_right = n - (i + 1);
			while (!st.empty() && digit < st.top().digit && cur_right >= st.top().rest)
				st.pop();
			int rest = st.empty() ? m - 1 : st.top().rest - 1;
			if (rest >= 0)
				st.push({ digit, rest });
		}
		string ans;
		while (!st.empty())
		{
			ans.push_back(st.top().digit);
			st.pop();
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}

	string remove_zero(const string &number)
	{
		if (all_zero(number))
			return "0";
		int start = 0;
		while (number[start] == '0')
			start++;
		string ans;
		for (int i = start; i < int(number.length()); i++)
			ans.push_back(number[i]);
		return ans;
	}

	bool all_zero(const string &number)
	{
		for (char digit : number)
			if (digit != '0')
				return false;
		return true;
	}

};

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	string num = "112";
	int k = 1;
	cout << (new Solution())->removeKdigits(num, k) << endl;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

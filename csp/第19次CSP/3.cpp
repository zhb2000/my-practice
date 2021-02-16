//Markdown渲染器
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

//trim [l,r]
string trim(const string &str, int l, int r)
{
	if (r < l)
		return "";
	int tl;
	for (tl = l; tl <= r; tl++)
		if (str[tl] != ' ')
			break;
	int tr;
	for (tr = r; tr >= l; tr--)
		if (str[tr] != ' ')
			break;
	if (tr < tl)//str is all space
		return "";
	return str.substr(tl, clen(tl, tr));
}

string trim(const string &str)
{
	return trim(str, 0, int(str.length()) - 1);
}

int calc_parag(const string &text, int w)
{
	assert(!text.empty());
	int ans = 0;
	int i = 0;
	while (true)
	{
		i += w;
		ans += 1;
		if (i < int(text.length()))
		{
			while (i < int(text.length()) && text[i] == ' ')
				i++;
		}
		else
			break;
	}
	return ans;
}

enum ElemType { Blank, Li, Parag };

struct Elem
{
	ElemType type;
	string text;
	void append_li(const string &line)
	{
		assert(type == Li);
		if (text.length() > 0)
			text.push_back(' ');
		text.append(trim(line, 2, int(line.length()) - 1));
	}
	void append_parag(const string &line)
	{
		assert(type == Parag);
		assert(text.length() > 0);
		text.push_back(' ');
		text.append(trim(line));
	}
	int get_lines(int w) const
	{
		if (type == Blank)
			return 1;
		else if (type == Li)
		{
			if (text.empty())
				return 1;
			else
				return calc_parag(text, w - 3);
		}
		else
			return calc_parag(text, w);
	}
	
	static Elem make_blank() { return { Blank,"" }; }
	static Elem make_li(const string &line)
	{
		return { Li,trim(line, 2, int(line.length()) - 1) };
	}
	static Elem make_parag(const string &line) { return { Parag,trim(line) }; }
};

ostream &operator<<(ostream &os, const Elem &e)
{
	if (e.type == Blank)
		os << "\n";
	else if (e.type == Li)
		os << " * " << e.text << "\n";
	else // Parag
		os << e.text << "\n";
	return os;
}

bool is_blank(const string &line)
{
	for (char ch : line)
		if (ch != ' ')
			return false;
	return true;
}

bool is_li_head(const string &line)
{
	return line.length() >= 2 && line[0] == '*' && line[1] == ' ';
}

bool is_li_rest(const string &line)
{
	return !is_blank(line) && line.length() > 2 && line[0] == ' ' && line[1] == ' ';
}

vector<Elem> elems;

int main()
{
#ifdef LOCAL
	freopen("in1.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	string line;
	getline(cin, line);
	int w = stoi(line);
	while (getline(cin, line))
	{
		if (is_blank(line))
		{
			if (!elems.empty() && elems.back().type != Blank)
				elems.push_back(Elem::make_blank());
		}
		else if (is_li_head(line))
		{
			if (!elems.empty() && elems.back().type == Parag)
				elems.push_back(Elem::make_blank());
			elems.push_back(Elem::make_li(line));
		}
		else if (!elems.empty() && elems.back().type == Li && is_li_rest(line))
			elems.back().append_li(line);
		else
		{
			if (elems.empty() || elems.back().type == Blank)
				elems.push_back(Elem::make_parag(line));
			else if (elems.back().type == Li)
			{
				elems.push_back(Elem::make_blank());
				elems.push_back(Elem::make_parag(line));
			}
			else
				elems.back().append_parag(line);
		}
	}
	while (!elems.empty() && elems.back().type == Blank)
		elems.pop_back();

#ifdef DEBUG
	for (int i = 0; i < int(elems.size()); i++)
		cout << i+1 << ": " << elems[i];
#endif // DEBUG

	int ans = 0;
	for (const Elem &e : elems)
		ans += e.get_lines(w);
	cout << ans;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
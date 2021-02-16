//化学方程式
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

template<class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	os << "[";
	bool isfirst = true;
	for (const auto &x : v)
	{
		if (isfirst)
			isfirst = false;
		else
			os << ", ";
		os << x;
	}
	os << "]";
	return os;
}

struct Element
{
	char data[3];
	bool operator==(const Element &other) const
	{
		return strcmp(data, other.data) == 0;
	}
};
namespace std
{
	template<>
	struct hash<Element>
	{
		size_t operator()(const Element &e) const
		{
			size_t result = 0;
			for (const char *p = e.data; *p != '\0'; p++)
			{
				int num;
				char ch = *p;
				if (isupper(ch))
					num = ch - 'A' + 1;
				else
					num = ch - 'a' + 1 + 29;
				result = result * 101 + num;
			}
			return result;
			//return hash<string>{}(string(e.data));
		}
	};
}
ostream &operator<<(ostream &os, const Element &e)
{
	os << e.data;
	return os;
}

enum class Tag { elem, lbrace, rbrace, number };
struct Token
{
	Tag tag;
	Element element;
	int number;
	
	static Token make_brace(char ch)
	{
		assert(ch == '(' || ch == ')');
		Token token;
		if (ch == '(')
			token.tag = Tag::lbrace;
		else
			token.tag = Tag::rbrace;
		return token;
	}
	static Token make_number(int number)
	{
		Token token;
		token.tag = Tag::number;
		token.number = number;
		return token;
	}
	static Token make_elem(const string &elem)
	{
		assert(elem.length() == 1 || elem.length() == 2);
		Token token;
		token.tag = Tag::elem;
		strcpy(token.element.data, elem.c_str());
		return token;
	}
};

ostream &operator<<(ostream &os, const Token &token)
{
	os << "[";
	if (token.tag == Tag::elem)
		os << token.element.data;
	else if (token.tag == Tag::lbrace)
		os << "(";
	else if (token.tag == Tag::rbrace)
		os << ")";
	else
		os << token.number;
	os << "]";
	return os;
}

template<class K, class V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &dict)
{
	os << "{";
	for (const auto &p : dict)
		os << p.first << ": " << p.second << ", ";
	os << "}";
	return os;
}

//[l,r]
void split_hxs(const string &s, int l, int r, vector<Token> &hxs)
{
	hxs.clear();
	int number = 0;
	string elem;
	for (int i = l; i <= r; i++)
	{
		if (isdigit(s[i]))
		{
			number = number * 10 + (s[i] - '0');
		}
		else
		{
			if (number != 0)
			{
				hxs.push_back(Token::make_number(number));
				number = 0;
			}

			if (s[i] == '(' || s[i] == ')')
				hxs.push_back(Token::make_brace(s[i]));
			else
			{
				assert(isupper(s[i]));
				assert(elem.empty());
				elem.push_back(s[i]);
				if (i + 1 <= r && islower(s[i + 1]))
				{
					elem.push_back(s[i + 1]);
					i += 1;
				}
				hxs.push_back(Token::make_elem(elem));
				elem.clear();
			}
		}
	}
	if (number != 0)
		hxs.push_back(Token::make_number(number));
}

//[l,r]
unordered_map<Element, int> parse_hxs(const vector<Token> &hxs, int l, int r)
{
	unordered_map<Element, int> dict;
	stack<int> st;
	for (int i = l; i <= r; i++)
	{
		assert(!(st.empty() && hxs[i].tag == Tag::number));
		if (hxs[i].tag == Tag::lbrace)
			st.push(i);
		else if (hxs[i].tag == Tag::rbrace)
		{
			int lb = st.top(); st.pop();
			if (st.empty())
			{
				unordered_map<Element, int> temp_dict = parse_hxs(hxs, lb + 1, i - 1);
				int number;
				if (i + 1 <= r && hxs[i + 1].tag == Tag::number)
				{
					number = hxs[i + 1].number;
					i += 1;
				}
				else
					number = 1;
				for (const auto &pir : temp_dict)
				{
					Element k = pir.first;
					int v = pir.second;
					if (dict.count(k) > 0)
						dict[k] += v * number;
					else
						dict[k] = v * number;
				}
			}
		}
		else if (st.empty() && hxs[i].tag == Tag::elem)
		{
			Element elem = hxs[i].element;
			int number;
			if (i + 1 <= r && hxs[i + 1].tag == Tag::number)
			{
				number = hxs[i + 1].number;
				i += 1;
			}
			else
				number = 1;
			if (dict.count(elem) > 0)
				dict[elem] += number;
			else
				dict[elem] = number;
		}
	}
	return dict;
}

void split_with_plus(const string &str, int l, int r, vector<Pii> &result)
{
	result.clear();
	int ll = l;
	for (int i = l; i <= r; i++)
	{
		if (str[i] == '+')
		{
			result.emplace_back(ll, i - 1);
			ll = i + 1;
		}
	}
	result.emplace_back(ll, r);
}

unordered_map<Element, int> get_dict(const string &s, const vector<Pii> &oneside)
{
	unordered_map<Element, int> dict;
	vector<Token> hxs;
	for (const Pii &pir : oneside)
	{
		hxs.clear();
		split_hxs(s, pir.first, pir.second, hxs);
#ifdef DEBUG1
		cout << pir.first << "~" << pir.second << ": ";
		for (const auto &token : hxs)
			cout << token << " ";
		cout << endl;
#endif // DEBUG

		int l = (hxs.front().tag == Tag::number) ? 1 : 0;
		auto temp = parse_hxs(hxs, l, int(hxs.size()) - 1);
		if (l == 1)
		{
			int num = hxs.front().number;
			for (const auto &p : temp)
				temp[p.first] *= num;
		}
		for (const auto &p : temp)
		{
			Element k = p.first;
			int v = p.second;
			if (dict.count(k) > 0)
				dict[k] += v;
			else
				dict[k] = v;
		}
	}
	return dict;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	string str;
	vector<Pii> lpairs, rpairs;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> str;
		int eq_pos = 0;
		for (int i = 0; i < int(str.length()); i++)
		{
			if (str[i] == '=')
			{
				eq_pos = i;
				break;
			}
		}
		lpairs.clear(); rpairs.clear();
		split_with_plus(str, 0, eq_pos - 1, lpairs);
		split_with_plus(str, eq_pos + 1, int(str.length()) - 1, rpairs);
#ifdef DEBUG
		cout << "lpairs: " << lpairs << endl;
		cout << "rpairs: " << rpairs << endl;
		cout << "ldict: " << get_dict(str, lpairs) << endl;
		cout << "rdict: " << get_dict(str, rpairs) << endl;
#endif // DEBUG

		if (get_dict(str, lpairs) == get_dict(str, rpairs))
			cout << "Y\n";
		else
			cout << "N\n";
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
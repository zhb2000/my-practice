#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LOCAL
#define DEBUG
//#define CONSOLE_PAUSE


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

struct Record
{
	char type;
	string site;
	string date;
	string testee;
	int score;
	string to_card() const
	{
		string s;
		s.push_back(type);
		return s.append(site).append(date).append(testee);
	}
};

Record make_record(const string &s, int score)
{
	char type = s[1 - 1];
	string site = s.substr(2 - 1, 4 - 2 + 1);
	string date = s.substr(5 - 1, 10 - 5 + 1);
	string testee = s.substr(11 - 1, 13 - 11 + 1);
	return Record{ type,site,date,testee,score };
}

struct EntryTp1
{
	string card;
	int score;
	bool operator<(const EntryTp1 &other) const
	{
		if (score == other.score)
			return card < other.card;
		return score > other.score;
	}
};

struct EntryTp2
{
	int testee_tot;
	int score_tot;
};

struct EntryTp3
{
	string site;
	int testee_tot;
	bool operator<(const EntryTp3 &other) const
	{
		if (testee_tot == other.testee_tot)
			return site < other.site;
		return testee_tot > other.testee_tot;
	}
};

vector<Record> records;
int n, m;
unordered_map<char, vector<EntryTp1>> ans_type1;
unordered_map<string, EntryTp2> ans_type2;
unordered_map<string, vector<EntryTp3>> ans_type3;

void build_ans_tp1(char type)
{
	if (ans_type1.count(type) > 0)
		return;
	ans_type1[type] = {};
	auto &v = ans_type1[type];
	for (const Record &record : records)
		if (record.type == type)
			v.push_back(EntryTp1{ record.to_card(), record.score });
	sort(v.begin(), v.end());
}

void build_ans_tp2(const string &site)
{
	if (ans_type2.count(site) > 0)
		return;
	int testee_tot = 0;
	int score_tot = 0;
	for (const Record &record : records)
	{
		if (record.site == site)
		{
			testee_tot += 1;
			score_tot += record.score;
		}
	}
	ans_type2[site] = EntryTp2{ testee_tot, score_tot };
}

void build_ans_tp3(const string &date)
{
	if (ans_type3.count(date) > 0)
		return;
	unordered_map<string, int> site_dict;//site->testee_tot
	for (const Record &record : records)
	{
		if (record.date == date)
		{
			if (site_dict.count(record.site) == 0)
				site_dict[record.site] = 0;
			site_dict[record.site] += 1;
		}
	}
	ans_type3[date] = {};
	auto &v = ans_type3[date];
	for (const auto &kv : site_dict)
		v.push_back(EntryTp3{ kv.first,kv.second });
	sort(v.begin(), v.end());
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif


	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string s; int score;
		cin >> s >> score;
		records.push_back(make_record(s, score));
	}
	for (int q = 1; q <= m; q++)
	{
		int qtype;
		cin >> qtype;
		if (qtype == 1)
		{
			char type;
			cin >> type;
			build_ans_tp1(type);
			printf("Case %d: 1 %c\n", q, type);
			const auto &v = ans_type1[type];
			if (v.empty())
				cout << "NA\n";
			else
			{
				for (const auto &e : v)
					cout << e.card << " " << e.score << "\n";
			}
		}
		else if (qtype == 2)
		{
			string site;
			cin >> site;
			build_ans_tp2(site);
			printf("Case %d: 2 %s\n", q, site.c_str());
			const EntryTp2 &e = ans_type2[site];
			if (e.testee_tot == 0)
			{
				assert(e.score_tot == 0);
				cout << "NA\n";
			}
			else
				cout << e.testee_tot << " " << e.score_tot << "\n";
		}
		else
		{
			assert(qtype == 3);
			string date;
			cin >> date;
			build_ans_tp3(date);
			printf("Case %d: 3 %s\n", q, date.c_str());
			const auto &v = ans_type3[date];
			if (v.empty())
				cout << "NA\n";
			else
			{
				for (const auto &e : v)
					cout << e.site << " " << e.testee_tot << "\n";
			}
		}
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}

#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>
#include<bitset>
#include<cctype>
#include<cstring>
using namespace std;
using ll = long long;
void cppio()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

unordered_map<string, string> dict;

bool str_same(const string &text, int index, const string &s)
{
	int len = int(s.size());
	for (int o = 0; o < len; o++)
	{
		char c1 = text[index + o];
		char c2 = s[o];
		if (tolower(c1) != tolower(c2))
			return false;
	}
	return true;
}

int str_find(const string &text, const string &s, int offset)
{
	int n = int(text.size());
	int len = int(s.size());
	for (int i = offset; i + len - 1 < n; i++)
	{
		if (str_same(text, i, s))
			return i;
	}
	return -1;
}

string replace_all(const string &text, const string &key, const string &value)
{
	string ans;
	int offset = 0;
	int n = int(text.size());
	int len = int(key.size());
	while (offset < n)
	{
		//int p = int(text.find(key, offset));
		int p = str_find(text, key, offset);
		if (p != -1)
		{
			string pre = text.substr(offset, p - offset);
			ans.append(pre);
			ans.append(value);
			offset = p + len;
		}
		else
		{
			ans.append(text.substr(offset, n - offset));
			offset = n;
		}
	}
	return ans;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif // LOCAL

	cppio();
	string line;
	getline(cin, line);
	int n = stoi(line);
	for (int c = 1; c <= n; c++)
	{
		string k, v;
		getline(cin, k);
		getline(cin, v);
		dict[k] = v;
	}
	string text;
	getline(cin, text);
	//cout << text << endl << endl;//
	for (const auto &p : dict)
	{
		text = replace_all(text, p.first, p.second);

		//cout << text << endl << endl;//
	}
	cout << text << "\n";

	return 0;
}

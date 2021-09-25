#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>
#include<bitset>
using namespace std;
using ll = long long;
void cppio()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

const int maxn = int(1e6 + 10);
bitset<maxn> is_composite;
int prime_index[maxn];

void filter_prime(int topn)
{
	int sqn = int(ceil(sqrt(topn)));
	for (int i = 2; i <= sqn; i++)
	{
		if (!is_composite[i])
		{
			for (int j = i * i; j <= topn; j += i)
				is_composite[j] = true;
		}
	}
}

bool isprime(int num)
{
	if (num == 1)
		return false;
	return !is_composite[num];
}

void make_index(int topn)
{
	int cnt = 0;
	for (int num = 2; num <= topn; num++)
	{
		if (!is_composite[num])
		{
			cnt++;
			prime_index[num] = cnt;
		}
	}
}

int rev(int num)
{
	string s = to_string(num);
	reverse(s.begin(), s.end());
	return stoi(s);
}

int digit_prod(int num)
{
	string s = to_string(num);
	int ans = 1;
	for (char ch : s)
	{
		int digit = ch - '0';
		ans *= digit;
	}
	return ans;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif // LOCAL

	cppio();
	int n1, n2, t;
	cin >> n1 >> n2 >> t;
	filter_prime(int(1e6 + 3));
	make_index(n2 + 3);
	for (int num = n1; num <= n2; num++)
	{
		if (!isprime(num))
			continue;
		int i = prime_index[num];
		int dprod = digit_prod(num);
		if (abs(i - dprod) <= t)
		{
			int rp = rev(num);
			if (isprime(rp))
			{
				int j = prime_index[rp];
				if (abs(j - rev(i)) <= t || abs(i - rev(j)) <= t)
				{
					cout << num << "\n";
				}
			}
		}
	}

	return 0;
}

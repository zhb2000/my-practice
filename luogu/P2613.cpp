//P2613 【模板】有理数取余
//快速幂求逆元
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
typedef pair<int, int> pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
template <class T>
inline bool isodd(T num) { return (num & 1) != 0; }
template <class T>
inline bool iseven(T num) { return (num & 1) == 0; }
inline int clen(int l, int r) { return r - l + 1; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;

const int MODU = 19260817;

ll quick_pow(ll a, ll n)
{
    if (n == 0)
        return 1 % MODU;
    ll x = quick_pow(a, n / 2);
    int ans = x * x % MODU;
    if (iseven(n))
        return ans;
    else
        return ans * (a % MODU) % MODU;
}

inline ll inv(ll a)
{
    return quick_pow(a, MODU - 2);
}

inline ll readnum()
{
    string s;
    cin >> s;
    ll ans = 0;
    for (char ch : s)
    {
        int num = ch - '0';
        ans = ans * 10 + num;
        ans %= MODU;
    }
    return ans;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

    ll a, b;
    a = readnum();
    b = readnum();
    if (b == 0)
        printf("Angry!");
    else
        printf("%lld", a * inv(b) % MODU);
	

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
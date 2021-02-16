//P1226 【模板】快速幂||取余运算
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
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class T>//两数平均
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
template <class T>//判断奇数
inline T isodd(T num) { return (num & 1) != 0; }
template <class T>//判断偶数
inline T iseven(T num) { return (num & 1) == 0; }
const int nonep = -1;
const int INTMAX = ~(1 << 31);

//递归
ll quick_pow(ll a, ll n, ll m)
{
    if (n == 0)
        return 1 % m;
    ll x = quick_pow(a, n / 2, m);
    ll ans = x * x % m;
    if (iseven(n))
        return ans;
    else
        return (ans * a) % m;
}
//非递归
ll quick_pow2(ll a, ll n, ll m)
{
    ll res = 1 % m;
    a = a % m;
    while (n > 0)
    {
        if ((n & 1) != 0)
            res = res * a % m;
        a = a * a % m;
        n = n >> 1;
    }
    return res;
}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ll a, b, k;
    scanf("%lld%lld%lld", &a, &b, &k);
    printf("%lld^%lld mod %lld=%lld", a, b, k, quick_pow2(a, b, k));


#ifdef CONSOLE_PAUSE
    system("PAUSE");
#endif
    return 0;
}
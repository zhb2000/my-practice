//P1082 同余方程
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
const int INTMAX = ~(1 << 31);

template <class T>
T exgcd(T a, T b, T& x, T& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    T d = exgcd(b, a % b, y, x);
    y -= x * (a / b);
    return d;
}

template<class T>
bool lieu(T a, T b, T c, T& x, T& y)
{
    T d = exgcd(a, b, x, y);
    if (c % d != 0)
        return false;
    T k = c / d;
    x *= k;
    y *= k;
    return true;
}

template<class T>
T rev(T a, T b)
{
    T x, y;
    T d = exgcd(a, b, x, y);
    x /= d;
    T t = b / d;
    x = (x % t + t) % t;
    return x;
}



int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", rev(a, b));


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
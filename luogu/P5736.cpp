//P5736 【深基7.例2】质数筛
//埃氏筛
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
template <class arrType>
inline arrType avg2(arrType a, arrType b) { return a + ((b - a) >> 1); }
const int nonep = -1;
const int INTMAX = ~(1 << 31);

const int maxn = 100000 + 5;
bool vis[maxn];
int n;

void calc()
{
    for (int i = 2; i < ceil(sqrt(maxn)); i++)
    {
        if (!vis[i])//i is prime
        {
            for (int j = i * i; j < maxn; j += i)
                vis[j] = true;
        }
    }
}
inline bool isprime(int num)
{
    if (num == 1)
        return false;
    return !vis[num];
}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    calc();

    scanf("%d", &n);
    bool isfirst = true;
    for (int c = 1; c <= n; c++)
    {
        int num;
        scanf("%d", &num);
        if (isprime(num))
        {
            if (isfirst)
                isfirst = false;
            else
                printf(" ");
            printf("%d", num);
        }
    }

#ifdef CONSOLE_PAUSE
    system("PAUSE");
#endif
    return 0;
}
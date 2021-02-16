//P3383 【模板】线性筛素数
//欧拉筛
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

const int maxn = (int)1e8 + 5;
bool composite[maxn];
vector<int> primes;

void calc(int n)
{
    for (int b = 2; b <= n; b++)
    {
        if (!composite[b])
            primes.push_back(b);
        for (int p : primes)
        {
            if (p * b > n)
                break;
            composite[p * b] = true;
            if (b % p == 0)
                break;
        }
    }
}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int n, q;
    scanf("%d%d", &n, &q);
    calc(n + 2);
    for (int c = 1; c <= q; c++)
    {
        int k;
        scanf("%d", &k);
        printf("%d\n", primes[k - 1]);
    }


#ifdef CONSOLE_PAUSE
    system("PAUSE");
#endif
    return 0;
}
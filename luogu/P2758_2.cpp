//P2758 编辑距离
//线性dp，递推求解
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 2000 + 5;
char A[maxn];
char B[maxn];
int f[maxn][maxn];

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    scanf("%s%s", A + 1, B + 1);
    int n = strlen(A + 1);
    int m = strlen(B + 1);

    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        f[i][0] = i;
    for (int j = 1; j <= m; j++)
        f[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = min(f[i - 1][j] + 1, min(f[i][j - 1] + 1, f[i - 1][j - 1] + (A[i] == B[j] ? 0 : 1)));

    printf("%d", f[n][m]);

    return 0;
}

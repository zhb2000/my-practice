#define LOCAL

#include <cstdio>
#include <iostream>
using namespace std;
using ll = long long;

void cpp_io()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main()
{
#ifdef LOCAL
    freopen("./in.txt", "r", stdin);
//    freopen("./out.txt", "w", stdout);
#endif

    cpp_io();
    ll n, m;
    cin >> n >> m;
    ll a = (1 + m) * m / 2;
    ll b = (m + m * n) * n / 2;
    ll ans = a + b - m;
    cout << ans;
    return 0;
}

//D - WA
//https://ac.nowcoder.com/acm/contest/15167/D
//贪心、排序
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
    Int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
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
inline Int avg2(Int a, Int b) { if (a > b) swap(a, b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { if (l > r) swap(l, r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------
 
const int INF = int(1e8);
const int maxn = int(5e5 + 5);
char s[maxn];
 
struct Interval
{
    int left_a;
    int right_a;
    Interval(int left_a, int right_a)
        :left_a(left_a), right_a(right_a) {}
    int len() const
    {
        return right_a - 1 - left_a;
    }
    bool operator<(const Interval &other) const
    {
        return len() < other.len();
    }
};
 
void fill_a(int l, int r)
{
    for (int i = l; i <= r; i++)
        s[i] = 'a';
}
 
int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
 
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", s);
    vector<Interval> intervals;
    int last_a_pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a')
        {
            if (last_a_pos == -1)
                last_a_pos = i;
            else
            {
                if (last_a_pos < i - 1)
                    intervals.push_back(Interval(last_a_pos, i));
                last_a_pos = i;
            }
        }
    }
    sort(intervals.begin(), intervals.end());
    for (const auto &x : intervals)
    {
        if (k <= 0)
        {
            assert(k == 0);
            break;
        }
        int use_num = min(x.len(), k);
        k -= use_num;
        fill_a(x.left_a + 1, x.left_a + use_num);
    }
    if (k > 0)
    {
        int a_seq_l = INF;
        int a_seq_r = -INF;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == 'a')
            {
                a_seq_l = min(a_seq_l, i);
                a_seq_r = max(a_seq_r, i);
            }
        }
        if (a_seq_l == INF) // no seq
        {
            assert(a_seq_r == -INF);
            fill_a(0, 0 + k - 1);
        }
        else
        {
            int use_num = min(k, a_seq_l - 0);
            k -= use_num;
            fill_a(a_seq_l - use_num, a_seq_l - 1);
            if (k > 0)
            {
                use_num = min(k, n - (a_seq_r + 1));
                k -= use_num;
                fill_a(a_seq_r + 1, a_seq_r + use_num);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        if (s[i] == 'a' && s[i - 1] == 'a')
            ans++;
    }
    printf("%d\n", ans);
    printf("%s", s);
 
 
#ifdef CONSOLE_PAUSE
    system("PAUSE");
#endif
    return 0;
}

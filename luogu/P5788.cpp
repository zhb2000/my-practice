//P5788 【模板】单调栈
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
#include<unordered_map>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class T>
inline T avg2(T a, T b) { return a + ((b - a) >> 1); }
const int nonep = -1;
const int INTMAX = ~(1 << 31);

template<class T, int maxNum>
struct Stack
{
	T elems[maxNum];
	int nxti;
	Stack()
	{
		clear();
	}
	void clear()
	{
		nxti = 0;
	}
	T& top()
	{
		return elems[nxti - 1];
	}
	bool empty()
	{
		return nxti == 0;
	}
	void push(T elem)
	{
		elems[nxti] = elem;
		nxti++;
	}
	void pop()
	{
		nxti--;
	}
	int size()
	{
		return nxti;
	}
};

const int maxn = 3 * (int)1e6 + 5;
int arr[maxn];
int f[maxn];
Stack<pii, maxn> s;//<index, number>

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &arr[i]);
	}
	s.push(make_pair(1, arr[1]));
	for (int i = 2; i <= n; i++)
	{
		while (!s.empty() 
			&& arr[i] > s.top().second)
		{
			f[s.top().first] = i;
			s.pop();
		}
		s.push(make_pair(i, arr[i]));
	}
	/*while (!s.empty())
	{
		f[s.top().first] = 0;
		s.pop();
	}*/
	bool isfirst = true;
	for (int i = 1; i <= n; i++)
	{
		if (isfirst)
			isfirst = false;
		else
			printf(" ");
		printf("%d", f[i]);
	}
		


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
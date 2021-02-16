//P1886 滑动窗口 /【模板】单调队列
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
struct Queue
{
	T elems[maxNum];
	int frontp, rearp;//[frontp, rearp)
	Queue()
	{
		clear();
	}
	void clear()
	{
		frontp = 0;
		rearp = 0;
	}
	T& front()
	{
		return elems[frontp];
	}
	T& back()
	{
		return elems[rearp - 1];
	}
	int size()
	{
		return rearp - frontp;
	}
	bool empty()
	{
		return size() == 0;
	}
	void push_back(T elem)
	{
		elems[rearp] = elem;
		rearp++;
	}
	void pop_front()
	{
		frontp++;
	}
	void pop_back()
	{
		rearp--;
	}
	void print()
	{
		for (int i = frontp; i != rearp; i++)
			printf("<i: %d, num: %d> ", elems[i].first, elems[i].second);
		printf("\n");
	}
};

const int maxn = (int)1e6 + 5;
int arr[maxn];
Queue<pii, maxn> qmax;//<index, number>
Queue<pii, maxn> qmin;
int n, k;
int ans_max[maxn];
int ans_min[maxn];
int ansi = 0;
int lefti, righti;

void numin(int i)
{
	while (!qmax.empty()
		&& arr[i] > qmax.back().second)
		qmax.pop_back();
	qmax.push_back(make_pair(i, arr[i]));

	while (!qmin.empty()
		&& arr[i] < qmin.back().second)
		qmin.pop_back();
	qmin.push_back(make_pair(i, arr[i]));
}

void numout(int i)
{
	if (!qmax.empty()
		&& i == qmax.front().first)
		qmax.pop_front();

	if (!qmin.empty()
		&& i == qmin.front().first)
		qmin.pop_front();
}

void getans()
{
#ifdef DEBUG
	printf("lefti: %d, righti: %d\n", lefti, righti);
	printf("qmin: ");
	qmin.print();
	//printf("qmax: ");
	//qmax.print();
	printf("\n");
	//printf("qmin fronti: %d, qmax fronti: %d\n", qmin.front().first, qmax.front().first);
#endif // DEBUG

	ans_max[ansi] = qmax.front().second;
	ans_min[ansi] = qmin.front().second;
	ansi++;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	for (int i = 0; i < k; i++)
		numin(i);
	getans();

	lefti = 0; righti = k - 1;
	for (int c = 1; c <= n - k; c++)
	{
		numout(lefti);
		lefti++;
		righti++;
		numin(righti);
		getans();
	}

	bool isfirst = true;
	for (int i = 0; i != ansi; i++)
	{
		if (isfirst)
			isfirst = false;
		else
			printf(" ");
		printf("%d", ans_min[i]);
	}
	printf("\n");
	isfirst = true;
	for (int i = 0; i != ansi; i++)
	{
		if (isfirst)
			isfirst = false;
		else
			printf(" ");
		printf("%d", ans_max[i]);
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
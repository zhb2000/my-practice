#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<cassert>

using namespace std;

const int INF = int(1e9);
using Pii = pair<int,int>;
template<class Int>
Int clen(Int l, Int r)
{
	if(l>r)
		swap(l,r);
	return r-l+1;
}
//--------- header -----------------

const int maxt = int(1e3+5);
Pii points[maxt];
int value[maxt];
int presum[maxt];

bool in_sqaure(const Pii &p, int xl, int yd, int xr, int yu)
{
	int x=p.first,y=p.second;
	return xl<=x&&x<=xr && yd<=y&&y<=yu;
}

void calc_value(int t, int xl, int yd, int xr, int yu)
{
	for(int i=1;i<=t;i++)
		value[i]=(in_sqaure(points[i],xl,yd,xr,yu))?1:0;
}

void calc_presum(int t)
{
	presum[0]=0;
	for(int i=1;i<=t;i++)
		presum[i]=value[i]+presum[i-1];
}

bool is_pass(int t)
{
	for(int i=1;i<=t;i++)
	{
		assert(value[i]==0||value[i]==1);
		if(value[i]==1)
			return true;
	}
	return false;
}

bool is_stay(int t, int k)
{
	for(int i=1;i+k-1<=t;i++)
	{
		int l=i, r=i+k-1;
		int sum=presum[r]-presum[l-1];
		assert(sum<=k);
		if(sum==k)
			return true;
	}
	return false;
}


int main()
{
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif

	int n,k,t,xl,yd,xr,yu;
	scanf("%d%d%d%d%d%d%d",&n,&k,&t,&xl,&yd,&xr,&yu);
	int passer=0,stayer=0;
	for(int ct=1;ct<=n;ct++)
	{
		for(int i=1;i<=t;i++)
			scanf("%d%d",&points[i].first,&points[i].second);
		calc_value(t,xl,yd,xr,yu);
		calc_presum(t);
		if(is_pass(t))
			passer++;
		if(is_stay(t,k))
			stayer++;
	}
	printf("%d\n",passer);
	printf("%d",stayer);
	
	return 0;
}
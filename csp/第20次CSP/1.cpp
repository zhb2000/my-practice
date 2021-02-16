#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>

using namespace std;

const int INF = int(1e9);
using Pii = pair<int,int>;

int min_dist[3];
int points[3];

int dist(const Pii &point, int x, int y)
{
	int dx = point.first-x;
	int dy = point.second-y;
	return dx*dx+dy*dy;
}

void init()
{
	for(int i=0;i<3;i++)
		min_dist[i]=INF;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif

	init();
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++)
	{
		int x0,y0;
		scanf("%d%d",&x0,&y0);
		Pii p=make_pair(x0,y0);
		int d=dist(p,x,y);
		if(d<min_dist[2])
		{
			min_dist[2]=d;
			points[2]=i;
			if(d<min_dist[1])
			{
				swap(min_dist[1],min_dist[2]);
				swap(points[1],points[2]);
				if(d<min_dist[0])
				{
					swap(min_dist[0],min_dist[1]);
					swap(points[0],points[1]);
				}
			}
		}
	}
	for(int i=0;i<3;i++)
	{
		printf("%d",points[i]);
		if(i<=2)
			printf("\n");
	}
	
	
	return 0;
}
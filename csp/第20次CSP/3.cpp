#ifndef LOCAL
#define NDEBUG//close assert
#endif
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<cassert>
#include<string>
#include<cctype>

using namespace std;

using Pii = pair<int,int>;
template<class Int>
Int clen(Int l, Int r)
{
	if(l>r)
		swap(l,r);
	return r-l+1;
}
//[l,r]
int stoint(const string &s, int l, int r)
{
	int number=0;
	for(int i=l;i<=r;i++)
	{
		assert(isdigit(s[i]));
		int digit=s[i]-'0';
		number=number*10+digit;
	}
	return number;
}
const int INF = int(1e9);
template<class T>
ostream& operator<<(ostream &os, const vector<T> &v)
{
	os<<"[";
	bool isfirst=true;
	for(const auto &x : v)
	{
		if(isfirst)
			isfirst=false;
		else
			os<<", ";
		os<<x;
	}
	os<<"]";
	return os;
}
//--------- header -----------------

struct DoorInput
{
	bool isI;
	int index;
	
	DoorInput(const string &str)
	{
		assert(str.length()>=2);
		assert(str[0]=='O' || str[0]=='I');
		isI = (str[0]=='I');
		index=stoint(str,1,int(str.length())-1);
	}
	bool get() const;
};

struct Door
{
	string func;
	vector<DoorInput> inputs;
	bool result;
	bool has_result;
	
	bool output();
	void reset_input()
	{
		inputs.clear();
		has_result=false;
	}
	void reset_result()
	{
		has_result=false;
	}
	static bool bxor(bool a, bool b)
	{
		return (a&&!b)||(!a&&b);
	}
};

const int maxn = 500+5;//num of door
const int maxk = 5+2;//num of in of a door
const int maxm = maxn*maxk;//num of input signal
const int maxqs = int(1e4+5);//num of question

bool input_signals[maxm];
Door doors[maxn];

vector<bool> q_in[maxqs];
vector<int> q_want[maxqs];

bool DoorInput::get() const
{
	if(isI)
		return input_signals[index];
	else
		return doors[index].output();
}

bool Door::output()
{
	if(has_result)
		return result;
	if(func=="NOT")
	{
		assert(inputs.size()==1);
		result = !inputs[0].get();
	}
	else if(func=="AND")
	{
		assert(inputs.size()>=2);
		result = inputs[0].get();
		for(int i=1;i<int(inputs.size());i++)
			result = result && inputs[i].get();
	}
	else if(func=="OR")
	{
		assert(inputs.size()>=2);
		result = inputs[0].get();
		for(int i=1;i<int(inputs.size());i++)
			result = result || inputs[i].get();
	}
	else if(func=="XOR")
	{
		assert(inputs.size()>=2);
		result = inputs[0].get();
		for(int i=1;i<int(inputs.size());i++)
			result = bxor(result, inputs[i].get());
	}
	else if(func=="NAND")
	{
		assert(inputs.size()>=2);
		result = inputs[0].get();
		for(int i=1;i<int(inputs.size());i++)
			result = result && inputs[i].get();
		result = !result;
	}
	else//NOR
	{
		assert(func=="NOR");
		assert(inputs.size()>=2);
		result = inputs[0].get();
		for(int i=1;i<int(inputs.size());i++)
			result = result || inputs[i].get();
		result = !result;
	}
	has_result=true;
	return result;
}

int vis[maxn];
vector<int> G[maxn];

bool dfs(int u)
{
	vis[u]=-1;
	for(int v : G[u])
	{
		if(vis[v]<0)
			return false;
		else if(vis[v]==0)
			if(!dfs(v))
				return false;
	}
	vis[u]=1;
	return true;
}

bool nocircle(int n)
{
	for(int i=1;i<=n;i++)
		vis[i]=0;
	for(int u=1;u<=n;u++)
		if(vis[u]==0)
			if(!dfs(u))
				return false;
	return true;
}


void init_case(int n)
{
	for(int i=0;i<=n;i++)
	{
		doors[i].reset_input();
		G[i].clear();
	}
}

void clear_questions(int qs)
{
	for(int i=0;i<=qs;i++)
	{
		q_in[i].clear();
		q_want[i].clear();
	}
}

void init_question(int n)
{
	for(int i=0;i<=n;i++)
	{
		doors[i].reset_result();
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	//TODO sync
	
	int T;
	cin>>T;
	for(int kase=1;kase<=T;kase++)
	{
		int m,n;
		cin>>m>>n;
		init_case(n);
		for(int i=1;i<=n;i++)
		{
			cin>>doors[i].func;
			int k;
			cin>>k;
			string door_in;
			for(int ct=1;ct<=k;ct++)
			{
				cin>>door_in;
				doors[i].inputs.push_back(DoorInput(door_in));
				assert(door_in[0]=='O'||door_in[0]=='I');
				if(door_in[0]=='O')
				{
					int from = stoint(door_in, 1, int(door_in.length())-1);
					G[from].push_back(i);
				}
			}
		}
		
#ifdef DEBUG1
		for(int i=1;i<=n;i++)
			cout<<"G["<<i<<"]: "<<G[i]<<endl;
#endif
		
		int qs;
		cin>>qs;
		clear_questions(qs);
		for(int i=1;i<=qs;i++)
		{
			for(int ct=1;ct<=m;ct++)
			{
				int sig;
				cin>>sig;
				assert(sig==0||sig==1);
				q_in[i].push_back(sig!=0);
			}
		}
		for(int i=1;i<=qs;i++)
		{
			int wantnum;
			cin>>wantnum;
			for(int ct=1;ct<=wantnum;ct++)
			{
				int index;
				cin>>index;
				q_want[i].push_back(index);
			}
		}
		
		if(nocircle(n))
		{
			for(int q=1;q<=qs;q++)
			{
				init_question(n);
				assert(int(q_in[q].size())==m);
				for(int i=0;i<m;i++)
					input_signals[i+1]=q_in[q][i];
				
				bool isfirst=true;
				for(int index : q_want[q])
				{
					if(isfirst)
						isfirst=false;
					else
						cout<<" ";
					cout<<(doors[index].output() ? 1 : 0);
				}
				cout<<"\n";
			}
		}
		else
		{
			cout<<"LOOP\n";
		}
		
		
	}
	
	return 0;
}
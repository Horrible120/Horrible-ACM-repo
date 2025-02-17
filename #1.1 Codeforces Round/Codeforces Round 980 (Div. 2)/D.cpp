#include<bits/stdc++.h>
using namespace std;

const long long INF=1e18;
long long tt;
long long tot;

struct Node
{
	long long u,a,b,fir;
	long long dis,pre;
	bool vis;
	Node():fir(-1),vis(false),dis(INF),pre(0){}
	
	bool operator > (const Node &a) const
	{
		return dis>a.dis;
	}
}node[400010];

struct Edge
{
	long long u,v,w,next;
	Edge():next(-1){}
	Edge(long long _u,long long _v,long long _w,long long _next):
		u(_u),v(_v),w(_w),next(_next){}
}edge[1000010];



void add_edge(long long u,long long v,long long w)
{
	edge[tot]={u,v,w,node[u].fir};
	node[u].fir=tot++;
}

void Dij(long long S)
{
	priority_queue<Node,vector<Node>,greater<Node>> q;
	q.push(node[S]);
	node[S].dis=0;
	while(!q.empty())
	{
		//cout<<"KKK";
		long long u=q.top().u;
		q.pop();
		if(node[u].vis) continue;
		else
		{
			node[u].vis=true;
			for(long long i=node[u].fir;~i;i=edge[i].next)
			{
				Edge e=edge[i];
				if(node[u].dis+e.w<node[e.v].dis)
				{
					node[e.v].dis=node[u].dis+e.w;
					q.push(node[e.v]);
				}
			}
		}	
	}
}

void init(int n)
{
	tot=0;
	for(int i=0;i<=n;i++)
		node[i]={};
	for(int i=0;i<=n*2;i++)
		edge[i]={};
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//int i=2,j=0;
	//j=(i++)+(++i)+(++i);
	//cout<<j<<endl;
	
	while(tt--)
	{
		int n;
		cin>>n;
		init(n);
		for(int i=1;i<=n;i++)
			cin>>node[i].a;
		for(int i=1;i<=n;i++)
			cin>>node[i].b;
		for(long long i=1;i<=n;i++)
		{
			add_edge(i,node[i].b,node[i].a);
			if(i>1)
				add_edge(i,i-1,0);
		}
		
		for(long long i=1;i<=n;i++)
			node[i].u=i;
		
		Dij(1);
		
		for(int i=1;i<=n;i++)
			node[i].pre=node[i-1].pre+node[i].a;
			
		long long ans=0;
			
		for(int i=1;i<=n;i++)
			ans=max(ans,node[i].pre-node[i].dis);
		
		/*
		for(int i=1;i<=n;i++)
		{
			cout<<">>";
			cout<<node[i].dis<<endl;
		}
		*/
		
		cout<<ans<<endl;
		
	}
	
	return 0;
}



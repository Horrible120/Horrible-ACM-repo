#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

const long long INF=1e18;

long long tt,n,tot,cnt,S,T;

struct Edge
{
	long long u,v,cap,flow;
	long long next;
	Edge()
	{
		u=0;
		v=0;
		cap=0;
		flow=0;
		next=-1;		//待调整 
	}
}edge[20010];

struct Node
{
	long long num,dep,wt;
	long long cur,fir;
	
	Node()
	{
		num=0;
		dep=0;
		wt=0;		
		cur=-1;	//待调整 
		fir=-1;	//待调整 
	}
}node[201];

void add_edge(long long u,long long v,long long cap)
{
	edge[tot].u=u;
	edge[tot].v=v;
	edge[tot].cap=cap;
	edge[tot].flow=0;
	edge[tot].next=node[u].fir;
	node[u].fir=tot;
	tot++;
	
	edge[tot].u=v;
	edge[tot].v=u;
	edge[tot].cap=0;
	edge[tot].flow=0;
	edge[tot].next=node[v].fir;
	node[v].fir=tot;
	tot++;
}

void build_map()
{
	//1~60位次 
	for(long long i=1;i<=60;i++)
	{
		add_edge(i,T,1);
		node[i].wt=-1;
	}
	for(long long i=61;i<=60+cnt;i++)
	{
		add_edge(S,i,1);
		node[i].wt=1;
		for(long long j=1;j<=60;j++)
			if(node[i].num&(1ll<<(j-1)))
				add_edge(i,j,INF);
	}
}

int BFS()
{
	for(int i=1;i<=cnt+62;i++)
		node[i].dep=0;
	
	queue<long long> q;
	q.push(S);
	node[S].dep=1;
	
	while(!q.empty())
	{
		long long u=q.front();
		q.pop();
		for(long long i=node[u].fir;~i;i=edge[i].next)
		{
			Edge e=edge[i];
			if((!node[e.v].dep)&&(e.cap>e.flow))
			{
				node[e.v].dep=node[u].dep+1;
				//if(e.v==T)
				//	return 1;
				q.push(e.v);
			}
		}
	}
	return node[T].dep;
}

long long DFS(int u,long long flow)//NM$L
{
	if((u==T)||(!flow))
		return flow;
		
	long long ret=0;
	for(long long &i=node[u].cur;~i;i=edge[i].next)
	{
		Edge &e=edge[i];
		long long v=e.v,d=0;
		
		if((node[v].dep==node[u].dep+1)&&(d=DFS(v,min(flow-ret,e.cap-e.flow)))) 
		{
			ret+=d;
			e.flow+=d;
			
			edge[i^1ll].flow-=d;
			
			if(ret==flow)
				return ret;
		}
		//cout<<(i^1ll)<<endl;
	}
	return ret;
}

long long Dinic()
{
	//edge[124].flow=0;
	long long maxflow=0;
	while(BFS())
	{
		for(int i=1;i<=cnt+62;i++)
			node[i].cur=node[i].fir;
		maxflow+=DFS(S,INF);
	}
	return maxflow;
}

void init()
{
	cnt=0; 
	tot=0;
	
	for(int i=0;i<=20000;i++)
		edge[i]=Edge{};
		
	for(int i=1;i<=200;i++)
		node[i]=Node{};
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		
		cin>>n;
		
		init();
		
		long long x;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(x)
				node[60+(++cnt)].num=x;
		}
		S=cnt+61;
		T=cnt+62;
		build_map();
		
		cout<<(n-Dinic())<<endl;
	}

	return 0;
}


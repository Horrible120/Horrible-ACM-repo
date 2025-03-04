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

int tt;
int S,T;

struct Edge
{
	long long c,u,v,next,f;
	Edge (){}
};

struct Node
{
	long long w,first,dis,cur,dep;
	Node (){}
};

Node node[200];
Edge edge[20010];
int tot,n;

void add_edge(int u,int v)
{
	edge[tot].u=u;
	edge[tot].v=v;
	edge[tot].next=node[u].first;
	edge[tot].c=1; 
	node[u].first=tot;
	++tot;
	
	edge[tot].u=v;
	edge[tot].v=u;
	edge[tot].next=node[v].first;
	edge[tot].c=0; 
	node[v].first=tot;
	++tot;
}

void add(long long x,long long p)
{
	node[60+p].w=1;
	for(int i=1;i<=60;i++)
	{
		if(x&(1<<(i-1)))
		{
			edge[tot].u=p;
			edge[tot].v=i;
			edge[tot].next=node[p].first;
			edge[tot].c=INF; 
			node[p].first=tot;
			++tot;
			
			edge[tot].u=i;
			edge[tot].v=p;
			edge[tot].next=node[i].first;
			edge[tot].c=0;
			node[i].first=tot;
			++tot;
		}
	}
}

int BFS()
{
	queue<long long> q;
	
	for(int i=1;i<=n+62;i++)
		node[i].dep=0;
	
	node[S].dep=1;
	q.push(S);
	
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		for(Edge i=edge[node[cur].first];i.v;i=edge[i.next])
		{
			if(!node[i.v].dep&&i.c>i.f)
			{
				node[i.v].dep=node[cur].dep+1;
				q.push(i.v);
			}
		}
	}
	return node[T].dep;
}

int DFS(int u,long long flow)
{
	if((u==T)||(!flow))
		return flow;
	else
	{
		long long ret=0,d;
		for(long long &i=node[u].cur;edge[i].u;i=edge[i].next)
		{
			Edge &I=edge[i];
			if ((node[I.v].dep==node[I.u].dep+1)&&
				(d=DFS(I.v,min(flow-ret,I.c-I.f))))
			{
				ret+=d;
				I.f+=d;
				edge[i^1].f-=d;
			}
			if(ret==flow)
				return ret;
		}
		return ret;
	}
}

int Dinic()
{
	
	int maxflow=0;
	while(BFS())
	{cout<<"KKK"<<endl;
		for(int i=1;i<=60+n;i++)
			node[i].cur=node[i].first;
		maxflow+=DFS(S,INF);
	}
	return maxflow;
}

void init()
{
	tot=2;
	for(int i=1;i<=200;i++)
	{
		node[i].dis=INF;
		node[i].first=0;
		node[i].w=0;
	}
	for(int i=1;i<=15000;i++)
	{
		edge[i].u=0;
		edge[i].v=0;
		edge[i].next=0;
		edge[i].c=0;
		edge[i].f=0;
	}
	for(int i=1;i<=60;i++)
		node[i].w=-1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;
	
	while(tt--)
	{
		cin>>N;
		S=N+61;
		T=N+62;
		init();
		long long x;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(x) add(x,i+60);
		}
		for(int i=1;i<=60;i++)
			add_edge(i,T);
		for(int i=61;i<=60+n;i++)
			add_edge(S,i);
		//cout<<edge[0].u<<endl;
		cout<<n-Dinic()<<endl;
	}

	return 0;
}


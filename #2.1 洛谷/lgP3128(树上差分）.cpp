#include<cstdio>
#include<iostream>
using namespace std;

int N,K,tot;
int ans;

struct Edge
{
	int u,v,next;
}edge[100010];

struct Node
{
	int head=0;
	int dad[21]={};
	int son;
	int deep;
	int stress=0;
	bool book_1=0;
	bool book_2=0;
}node[50010];

void add_edge(int x,int y)
{
	edge[++tot].next=node[x].head;
	node[x].head=tot;
	edge[tot].u=x;
	edge[tot].v=y;
	return;
}

void DFS(int x)
{
	
	node[x].book_1=true;
	
	Edge cur=edge[node[x].head];
	while(cur.u)
	{
		if(!node[cur.v].book_1)
		{
			node[cur.v].deep=node[cur.u].deep+1;
			node[cur.v].dad[0]=cur.u;
		
			for(int i=1;i<=20;i++)
				node[cur.v].dad[i]=node[node[cur.v].dad[i-1]].dad[i-1];
		
			DFS(cur.v);
		}
		cur=edge[cur.next];
	}
	return;
}

int LCA(int x,int y)
{
	if(x==y) return x;
	if(node[x].deep<node[y].deep) swap(x,y);
	
	for(int i=20;i>=0;i--)
		if(node[x].deep-node[y].deep>=1<<i)
			x=node[x].dad[i];
			
	if(x==y) return x;
	
	for(int i=20;i>=0;i--)
		if(node[x].dad[i]!=node[y].dad[i])
		{
			x=node[x].dad[i];
			y=node[y].dad[i];
		}
	return node[x].dad[0];		
}

void solve(int x,int y)
{
	int fa=LCA(x,y);
	node[y].stress++;
	node[x].stress++;
	node[fa].stress--;
	node[node[fa].dad[0]].stress--;
}

void DFS_solve(int x)
{
	if(!node[x].head) return;
	node[x].book_2=true;
	for(Edge i=edge[node[x].head];i.u;i=edge[i.next])
	{
		if(!node[i.v].book_2)
		{
			DFS_solve(i.v);
			node[x].stress+=node[i.v].stress;	
		}
	}
	ans=max(ans,node[x].stress);
	return;
}

int main()
{
	scanf("%d%d",&N,&K);
	
	int x,y;
	for(int i=1;i<N;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	
	DFS(1);
	
	for(int i=1;i<=K;i++)
	{
		scanf("%d%d",&x,&y);
		//printf("%d\n",LCA(x,y));
		solve(x,y);
	}
	
	DFS_solve(1);
	
	printf("%d\n",ans);
	
	return 0;
 } 

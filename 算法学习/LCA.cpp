#include<queue>
#include<cstdio>
#include<iostream>
using namespace std;

int N,M,S,tot;

int ask[500010][2];

queue<int> que;

struct Edge
{
	int u,v;
	int next;
}edge[1000010];

struct Node
{
	int head=0;
	int deep;
	int dad[22]={};
	bool book;
}node[500010];

void add_edge(int a,int b)
{
		edge[++tot].next=node[a].head;
		edge[tot].u=a;
		edge[tot].v=b;
		node[a].head=tot;
}

void BFS()
{
	que.push(S);
	node[S].deep=0;
	node[S].book=true;
	
	Edge cur;
	
	while(!que.empty())
	{
		cur=edge[node[que.front()].head];
		while(cur.v)
		{
			if(!node[cur.v].book)
			{
				que.push(cur.v);
				node[cur.v].book=true;
				node[cur.v].deep=node[cur.u].deep+1;
				node[cur.v].dad[0]=cur.u;
				for(int i=1;i<=20;i++)
					node[cur.v].dad[i]=node[node[cur.v].dad[i-1]].dad[i-1];
			}
			
			cur=edge[cur.next];	 
		}
		que.pop();	
	}
	return;
}

int LCA(int x,int y)
{
	if(x==y) return x;
	if(node[x].deep<node[y].deep) swap(x,y);
	
	for(int i=20;i>=0;i--)
        if(node[x].deep-node[y].deep>=(1<<i))
            x=node[x].dad[i];
	
	//printf("(%d %d)",x,y);
	
	if(x==y) return x;
	
	for(int i=20;i>=0&&y!=x;i--)
		if(node[x].dad[i]!=node[y].dad[i])
		{
			x=node[x].dad[i];
			y=node[y].dad[i];
		}
	return node[x].dad[0];			
}

int main()
{
	scanf("%d%d%d",&N,&M,&S);
	
	int x,y;
	for(int i=1;i<N;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	
	BFS();
	
	/*for(int i=1;i<=N;i++)
		printf("%d\n",node[i].dad[0]);*/
	
	for(int i=1;i<=M;i++)
		scanf("%d%d",&ask[i][0],&ask[i][1]);
		
	for(int i=1;i<=M;i++)	
		printf("%d\n",LCA(ask[i][0],ask[i][1]));
	
	return 0;
 } 

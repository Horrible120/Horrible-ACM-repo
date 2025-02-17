#include<queue>
#include<cstdio>
using namespace std;

struct Edge
{
	int u,v,w;
	int next;
}edge[14010];

int n,m,start,end;
int first[3010];
int dis[14010];

queue <int> q;

void add_edge(int a,int b,int c,int i)
{
	if(first[a])
		edge[i].next=first[a];
	first[a]=i;
	edge[i].u=a;
	edge[i].v=b;
	edge[i].w=c;
}

void SPFA()
{
	int x,cur;
	
	for(int i=1;i<=n;i++)
		dis[i]=999999999;
	
	dis[start]=0;
	q.push(start);
	while(!q.empty()) 
	{
		x=q.front();
		q.pop();
		cur=first[x];
		while(cur)
		{
			if(dis[x]+edge[cur].w < dis[edge[cur].v])
			{
				dis[edge[cur].v] = dis[x]+edge[cur].w;
				q.push(edge[cur].v);
			}
				
			cur=edge[cur].next;
		}
	}
}

int main()
{
	
	scanf("%d%d%d%d",&n,&m,&start,&end);
	
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c,2*i-1);
		add_edge(b,a,c,2*i);
	}
	
	SPFA();
	
	printf("%d",dis[end]);
	
	return 0;
}

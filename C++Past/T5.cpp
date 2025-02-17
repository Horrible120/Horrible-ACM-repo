#include<queue>
#include<cstdio>
using namespace std;

struct Edge
{
	int u,v,w;
	int next;
}edge[100010];

int n,m,q,tot;
int first[100010];
long long dis[100010];

void add_edge(int a,int b,int c)
{	
	edge[++tot].u=a;
	edge[tot].v=b;
	edge[tot].w=c;
	if(first[a])
		edge[tot].next=first[a];
	first[a]=tot;
}

long long SPFA(int o)
{
	int x,cur;
	
	for(int i=1;i<=n;i++)
		dis[i]=9999999999999999;
	
	queue <int> q;
	
	dis[1]=0;
	q.push(1);
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
	if(dis[o]!=9999999999999999)
		return dis[o];
	else
		return -1;
}

int main()
{
	
	scanf("%d%d%d",&n,&m,&q);
	
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	
	int op,c,v,l;
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d",&v);
			printf("%lld\n",SPFA(v));
		}
		else
		{
			scanf("%d",&c);
			for(int j=1;j<=c;j++)
			{
				scanf("%d",&l);
				edge[l].w++;
			}
		}
	}
	
	return 0;
}

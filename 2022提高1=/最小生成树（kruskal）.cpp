#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Edge
{
	int u,v,w;
}edge[500010];

int n,m;
int dad[200010];
long long ans;

queue <int> q;

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

void add_edge(int a,int b,int c,int i)
{
	edge[i].u=a;
	edge[i].v=b;
	edge[i].w=c;
}

int find_dad(int x)
{
	if(dad[x]==x)
		return x;
	else
		return dad[x]=find_dad(dad[x]);
}

void kruskal()
{
	sort(edge+1,edge+m+1,cmp);
	
	int t=0,p=0;
	
	for(int i=1;i<=n;i++)
		dad[i]=i;
	
	while(t<n-1)
	{
		p++;
		if( find_dad(edge[p].u) != find_dad(edge[p].v))
		{
			dad[find_dad(edge[p].u)]=dad[find_dad(edge[p].v)];
			ans+=edge[p].w;
			t++;
		}
	}
}

int main()
{
	
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c,i);
	}
	
	kruskal();
	
	printf("%lld",ans);
	
	return 0;
}

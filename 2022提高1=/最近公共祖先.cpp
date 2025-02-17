#include<queue>
#include<cstdio>
using namespace std;

struct Edge
{
	int u,v;
	int next;
}edge[1000010];

int n,m;
int p[30];
int first[500010];
int dad[500010][25];
int deep[500010];
bool book[500010];

queue <int> q;

void add_edge(int a,int b,int i)
{
	if(first[a])
		edge[i].next=first[a];
	first[a]=i;
	edge[i].u=a;
	edge[i].v=b;
}

void BFS(int root)
{
	q.push(root);
	book[root]=true;
	deep[root]=1;
	
	int x,cur;
	
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		cur=first[x];
		
		while(cur)
		{
			if(!book[edge[cur].v])
			{
				book[edge[cur].v]=true;
				q.push(edge[cur].v);
				deep[edge[cur].v]=deep[x]+1;
				dad[edge[cur].v][0]=x;
			}
			cur=edge[cur].next;
		}	
	}
}

void LCA_pre()
{
	BFS(1);
	
	p[0]=1;
	for(int i=1;i<=21;i++)
		p[i]=p[i-1]*2;
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=21;j++)
			if(deep[i]-p[j]>0)
				dad[i][j]=dad[dad[i][j-1]][j-1];
}

int LCA_find(int a,int b)//a>=b
{
	if(deep[a]<deep[b])
		return LCA_find(b,a);
	else if(deep[a]>deep[b])
	{
		int sub=deep[a]-deep[b];
		for(int i=21;i>=0;i--)
			if(sub>=p[i])
			{
				a=dad[a][i];
				sub-=p[i];
			}
	}
	
	if(a==b)
		return a;
		
	for(int i=21;i>=0;i--)
		if(dad[a][i]!=dad[b][i])
		{
			a=dad[a][i];
			b=dad[b][i];
		}
	
	return dad[a][0];
}

int main()
{
	int a,b,c;
	
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b,2*i-1);
		add_edge(b,a,2*i);
	}
	
	LCA_pre();
	
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",LCA_find(a,b));
	}
	
	return 0;
}
/*
5 50
1 2
1 3
1 4
4 5
*/

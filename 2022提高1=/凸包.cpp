#include<cstdio>
#include<algorithm>
using namespace std;

struct Node
{
	int x,y;
}node[100010];

int n;
int sta[100010],top;
int ans;

bool cmp(Node a,Node b)
{
	if(a.x!=b.x)
		return a.x<b.x;
	return a.y>b.y;
}

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d%d",&node[i].x,&node[i].y);
	
	sort(node+1,node+n+1,cmp);
	
	for(int i=1;i<=n;i++)
	{
		if(top<2)
			sta[++top]=i;
		else
		{
			while(top>=2 && (node[sta[top]].x-node[sta[top-1]].x) * (node[i].y-node[sta[top-1]].y) - (node[i].x-node[sta[top-1]].x) * (node[sta[top]].y-node[sta[top-1]].y) < 0 )
				sta[top--]=0;
			sta[++top]=i;
		}
	}
	
	for(int i=1;i<=top;i++)
	{
		printf("(%d,%d) ",node[sta[i]].x,node[sta[i]].y);
		sta[i]=0;	
	} 
	printf("\n");
	top=0;
	
	for(int i=n;i>=1;i--)
	{
		if(top<2)
			sta[++top]=i;
		else
		{
			while(top>=2 && (node[sta[top]].x-node[sta[top-1]].x) * (node[i].y-node[sta[top-1]].y) - (node[i].x-node[sta[top-1]].x) * (node[sta[top]].y-node[sta[top-1]].y) < 0 )
				sta[top--]=0;
			sta[++top]=i;
		}
	}
	
	for(int i=1;i<=top;i++)
	{
		printf("(%d,%d) ",node[sta[i]].x,node[sta[i]].y);
		sta[i]=0;	
	} 
	printf("\n");
	top=0;
	
	return 0;
}

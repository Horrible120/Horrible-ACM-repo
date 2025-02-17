#include<cstdio>
using namespace std;

int n,m,ans;
int a,b;
int dad[1000010];
bool boss[1000010];

int getfa(int x)
{
	if(x[dad]==x)
		return x;
	else
		return x[dad]=getfa(x[dad]);
}

int main()
{
	scanf("%d%d",&n,&m);
	
	ans=n;
	
	for(int i=1;i<=n;i++)
	{
		dad[i]=i;
		boss[i]=1;
	}
		
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		
		if(getfa(a)!=getfa(b))
		{
			boss[getfa(a)]=0;
			dad[getfa(a)]=getfa(b);
			ans--;
		}
	}
	
	printf("%d\n",ans);
	
	for(int i=1;i<=n;i++)
		if(boss[i])
			printf("%d ",i);
	
	return 0;
}

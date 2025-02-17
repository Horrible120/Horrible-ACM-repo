#include<cstdio> 
using namespace std;
int map[40][40];
int x[1600],y[1600];
int n,m;
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	for(int i=1;i<=40;i++)
		for(int j=1;j<=40;j++)
			map[i][j]=0;
	scanf("%d",&n);
	m=n*n;
	x[1]=(n+1)/2;
	y[1]=1;
	map[(n+1)/2][1]=1;
	for(int i=2;i<=m;i++)
	{
		if(x[i-1]!=n&&y[i-1]==1)
		{
			y[i]=n;
			x[i]=x[i-1]+1;
			map[x[i-1]+1][n]=i;
			continue;
		}
		if(x[i-1]==n&&y[i-1]!=1)
		{
			x[i]=1;
			y[i]=y[i-1]-1;
			map[1][y[i-1]-1]=i;
			continue;
		}
		if(x[i-1]==n&&y[i-1]==1)
		{
			x[i]=n;
			y[i]=2;
			map[n][2]=i;
			continue;
		}
		if(x[i-1]!=n&&y[i-1]!=1)
		{
			if(!map[x[i-1]+1][y[i-1]-1])
			{
				x[i]=x[i-1]+1;
				y[i]=y[i-1]-1;
				map[x[i-1]+1][y[i-1]-1]=i;
				continue;
			}
			else
			{
				x[i]=x[i-1];
				y[i]=y[i-1]+1;
				map[x[i-1]][y[i-1]+1]=i;
				continue;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",map[i][j]);
		printf("\n");
	}
	return 0;
}

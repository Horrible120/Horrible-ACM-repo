#include<cstdio>
using namespace std;

int n;
int ans[40][40];

int main()
{
	scanf("%d",&n);
	
	ans[1][n/2+1]=1;
	
	int x=1,y=n/2+1;
	for(int i=2;i<=n*n;i++)
	{
		if(x==1&&y!=n)
		{
			ans[n][y+1]=i;
			x=n;
			y++;
			continue;
		}
		if(x!=1&&y==n)
		{
			ans[x-1][1]=i;
			y=1;
			x--;
			continue;
		}
		if(x==1&&y==n)
		{
			ans[x+1][y]=i;
			x++;
			continue;
		}
		if(x!=1&&y!=n)
		{
			if(!ans[x-1][y+1])
			{
				ans[x-1][y+1]=i;
				x--;
				y++;
				continue;
			}
			ans[x+1][y]=i;
			x++;
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	
	return 0;
}

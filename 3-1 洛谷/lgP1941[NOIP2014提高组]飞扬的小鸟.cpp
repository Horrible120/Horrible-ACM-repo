#include<cstdio>
#include<iostream>
using namespace std;

const int inf=0x3f3f3f3f;

int n,m,k;
int dp[1010][2];
int ans=0;

struct Ymove
{
	int up;
	int down;
	Ymove(){}
}ymove[10086];

struct Column
{
	bool If_co;
	int top,btm;
	Column(){};
}column[10086];

int main()
{	
	scanf("%d%d%d",&n,&m,&k);

	for(int i=0;i<n;i++)
		scanf("%d%d",&ymove[i].up,&ymove[i].down);
		
	int co,h,l;	
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d%d",&co,&l,&h);
		column[co].If_co=true;
		column[co].btm=l;
		column[co].top=h;
	}
	
	int dps=1;
	bool flag=0;
	
	for(int x=1;x<=n;x++)
	{
		dps=(dps+1)%2;//初始值为0 
		flag=true;
		
		for(int i=0;i<=m;i++)//初始化 
			dp[i][dps]=inf;
	
		for(int i=ymove[x-1].up+1;i<=m;i++)
			dp[i][dps]=min(dp[i-ymove[x-1].up][(dps+1)%2],dp[i-ymove[x-1].up][dps])+1;
			
		for(int i=m-ymove[x-1].up+1;i<=m;i++)
			dp[m][dps]=min(dp[m][dps],dp[i][(dps+1)%2]+1);
			
		for(int i=m-ymove[x-1].up+1;i<=m;i++)
			dp[m][dps]=min(dp[m][dps],dp[i][dps]+1);
				
		for(int i=1;i+ymove[x-1].down<=m;i++)
			dp[i][dps]=min(dp[i][dps],dp[i+ymove[x-1].down][(dps+1)%2]);
		
		if(column[x].If_co)
		{
			for(int i=1;i<=column[x].btm;i++)
				dp[i][dps]=inf;
			for(int i=column[x].top;i<=m;i++)
				dp[i][dps]=inf;
			for(int i=1;i<=m&&flag;i++)
				if(dp[i][dps]<inf)
					flag=false;
			if(!flag)
				ans++;
			else
			{
				printf("0\n%d",ans);
				return 0;
			}
		}
	}
	
	ans=inf;
	for(int i=1;i<=m;i++)
		ans=min(ans,dp[i][dps]);
	printf("1\n%d",ans);
	
	return 0;
 } 

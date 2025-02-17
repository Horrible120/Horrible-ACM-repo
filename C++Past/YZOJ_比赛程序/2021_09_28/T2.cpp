#include<cstdio>
#include<iostream>
using namespace std;

int n,m,q,k;
int cash[7];
int dp[7][510][8];
int face[7]={0,100,50,20,10,5,1};

int solve(int mon)
{
	int pf=mon%500;
	int ans=dp[6][pf][7];
	mon-=pf;
	
	int cas[7]={0,cash[1],cash[2],cash[3],cash[4],cash[5],cash[6]};
	
	for(int i=1;i<=6;i++)
		cas[i]-=dp[6][pf][i];
		
	for(int i=1;i<=6;i++)
	{
		ans+=min(mon/face[i],cas[i]);
		mon-=min(mon/face[i],cas[i])*face[i];
	}
	
	return ans;
	
}

int main()
{
	scanf("%d",&n);
	
	scanf("%d%d%d%d%d%d",&cash[1],&cash[2],&cash[3],&cash[4],&cash[5],&cash[6]);
	
	m=cash[1]*100+cash[2]*50+cash[3]*20+cash[4]*10+cash[5]*5+cash[6];
	
	q=cash[1]+cash[2]+cash[3]+cash[4]+cash[5]+cash[6];
	
	/****************************************************************/
	
	for(int i=1;i<=6;i++)
		for(int j=1;j<=499;j++)
			dp[0][j][7]=100010;
	for(int i=1;i<=6;i++)
		dp[i][0][7]=0;
	
	for(int i=1;i<=6;i++)//			±³°ü 
		for(int j=1;j<=499;j++)
		{
			dp[i][j][1]=dp[i-1][j][1];
			dp[i][j][2]=dp[i-1][j][2];
			dp[i][j][3]=dp[i-1][j][3];
			dp[i][j][4]=dp[i-1][j][4];
			dp[i][j][5]=dp[i-1][j][5];
			dp[i][j][6]=dp[i-1][j][6];
			dp[i][j][7]=dp[i-1][j][7];
			
			for(int s=1;s<=min(499,cash[i]);s++)
				if(j-s*face[i]>=0)
				{
					if(dp[i][j][7]>dp[i-1][j-s*face[i]][7]+s)
					{
						dp[i][j][1]=dp[i-1][j-s*face[i]][1];
						dp[i][j][2]=dp[i-1][j-s*face[i]][2];
						dp[i][j][3]=dp[i-1][j-s*face[i]][3];
						dp[i][j][4]=dp[i-1][j-s*face[i]][4];
						dp[i][j][5]=dp[i-1][j-s*face[i]][5];
						dp[i][j][6]=dp[i-1][j-s*face[i]][6];
						
						dp[i][j][7]=dp[i-1][j-s*face[i]][7]+s;
						dp[i][j][i]+=s;
					}
				}
				else
					break;
					
		}
	/*		
	for(int i=1;i<=100;i++)
	{
		printf("%d:  %d %d %d %d %d %d   %d\n",i,dp[6][i][1],dp[6][i][2],dp[6][i][3],dp[6][i][4],dp[6][i][5],dp[6][i][6],dp[6][i][7]);
	}	
	*/
	/********************************************************************/
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		
		if(k>m||dp[6][k%500][7]>500)
			printf("-1 -1\n");
		else
			printf("%d %d\n",solve(k),q-solve(m-k));	
	}
		
	return 0;
}

#include<cstdio>
#include<iostream>
using namespace std;

int n,m;
int w[40],c[40];
int dp[40][210];

int main()
{
	scanf("%d%d",&m,&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d%d",&w[i],&c[i]);
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(j>=w[i])
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+c[i]);
			else
				dp[i][j]=dp[i-1][j];
			
	printf("%d",dp[n][m]);
		
	return 0;
}

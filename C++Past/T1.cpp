#include<cstdio>
#include<iostream>
using namespace std;

int n,t;
int dp[210][210];
int c[210][12];

int main()
{
	scanf("%d%d",&n,&t);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=10;j++)
			scanf("%d",&c[i][j]);
	
	for(int i=n;i>=1;i--)
		for(int j=0;j<=t;j++)
			for(int k=10;k>=0;k--)
				if(j>=c[i][k])
					dp[i][j]=max(dp[i][j],dp[i+1][j-c[i][k]]+k*10);
					
	printf("%d",&dp[1][t]);
	
	return 0;
}

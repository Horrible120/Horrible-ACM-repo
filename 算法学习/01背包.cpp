#include<cstdio>
#include<iostream> 
using namespace std;

int N,M;

struct Goods
{
	int w,d;
}goods[3500];

int dp[13000];

int main()
{
	scanf("%d%d",&N,&M);
	
	for(int i=1;i<=N;i++)
		scanf("%d%d",&goods[i].w,&goods[i].d);
		
	for(int i=1;i<=N;i++)
		for(int j=M;j>=goods[i].w;j--)
			dp[j]=max(dp[j],dp[j-goods[i].w]+goods[i].d);
			
	printf("%d",dp[M]);
	
	return 0;
}

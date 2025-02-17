#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[2001],maxa,ans;
int dp[2001];
/*
dp[i]=0:不能够组成 
dp[i]=1:能够被若干张货币组成 
dp[i]=2:货币系统中固有的货币（若能被其他的组成则赋值为1）
*/ 
int main()
{
	freopen("money.in","r",stdin);
	freopen("money.out","r",stdout);
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&n);
		maxa=0;
		memset(dp,0,sizeof(dp));
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[j]);
			maxa=max(maxa,a[j]);
			dp[a[j]]=2;
		}
		sort(a+1,a+n+1);
		for(int j=1;j<=n;j++)
			for(int k=a[j];k<=maxa;k++)
				if(dp[k-a[j]])
					dp[k]=1;
		ans=n;
		for(int j=1;j<=n;j++)
			if(dp[a[j]]==1)
				ans--;
		printf("%d\n",ans);	
	}
	return 0;
}

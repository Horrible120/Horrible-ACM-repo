#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m;
const long long M=998244353;

long long w[510][510];
long long dp[510][510];

long long mad(long long x,long long y)
{
	return (x+y)%M;
}

long long mml(long long x,long long y)
{
	return (x*y)%M;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m;
	
	// 预处理:一种花色的牌中用了 j 张 1 的策略数 
	w[0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=i;j++)
			if(j)
				w[i][j]=mad(w[i-1][j-1],w[i-1][j+1]);
			else
				w[i][j]=w[i-1][j+1];
	
	// 动态规划 : 前 i 种花色 剩下 j 张 1 可用的策略数 
	for(int i=0;i<=m;i++)
		dp[1][i]=w[m][i];
	for(int i=2;i<=n;i++)
		 for(int j=0;j<=m;j++)
		 	for(int k=j;k<=m;k++)
		 		dp[i][j]=mad(dp[i][j],mml(dp[i-1][k],w[m][k-j]));
	
	for(int j=0;j<=n;j++,cout<<endl)
		for(int i=0;i<=m;i++)
  			cout << w[j][i] << ' ';
	cout<<dp[n][0]<<endl;
	
	return 0;
}

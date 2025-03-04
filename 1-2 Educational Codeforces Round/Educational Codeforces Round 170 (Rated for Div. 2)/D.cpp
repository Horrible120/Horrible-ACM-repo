#include<iostream>
#include<vector>
#include<string>
using namespace std;

int n,m;
int dp[5010][5010];
int d1[5010],d2[5010];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m;
	
	vector<int> v(n+1);
	
	for(int i=1;i<=n;i++)
		cin>>v[i];
	
	int cur=0,lst=1;
	for(int i=1;i<=n;i++)
	{
		if(v[i]==0)
		{
			if(cur==0)
			{
				cur++;
				lst=i+1;
				continue;
			}
			for(int j=0;j<=5000;j++)
				d1[j]=0,d2[j]=0;
			for(int j=lst;j<i;j++)
				if(v[j]>0) d1[v[j]]++;
				else d2[-v[j]]++;
			for(int j=1;j<=5000;j++)
			{
				d1[j]+=d1[j-1];
				d2[j]+=d2[j-1];
			}
			dp[cur][0]=dp[cur-1][0]+d1[0]+d2[cur];
			dp[cur][cur]=dp[cur-1][cur-1]+d1[cur]+d2[0];
			for(int j=1;j<cur;j++)
				dp[cur][j]=max(dp[cur-1][j-1],dp[cur-1][j])+d1[j]+d2[cur-j];
			lst=i+1;
			cur++;
		}
	}
	for(int j=0;j<=5000;j++)
		d1[j]=0,d2[j]=0;
	for(int j=lst;j<=n;j++)
		if(v[j]>0) d1[v[j]]++;
		else d2[-v[j]]++;
	for(int j=1;j<=5000;j++)
	{
		d1[j]+=d1[j-1];
		d2[j]+=d2[j-1];
	}
	dp[cur][0]=dp[cur-1][0]+d1[0]+d2[cur];
	dp[cur][cur]=dp[cur-1][cur-1]+d1[cur]+d2[0];
	for(int j=1;j<cur;j++)
		dp[cur][j]=max(dp[cur-1][j-1],dp[cur-1][j])+d1[j]+d2[cur-j];
	
	int ans=0;
	for(int i=0;i<=m;i++)
		ans=max(ans,dp[m][i]);
		
	cout<<ans<<endl;
	
	return 0;
}

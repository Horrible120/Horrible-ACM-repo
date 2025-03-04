#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

int t;
const long long Max=1e18;

int Find(vector<long long> &v,int i,int key)
{
	int l=0,r=i;
	int mid;
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(v[i]-v[mid]>key)
			l=mid;
		else
			r=mid;
	}
	if(v[i]-v[l]<=key)
		return l;
	else
		return r;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int n,m,flag=0;
		cin>>n>>m;
		vector<long long> a(n+1),b(m+1),pref(n+1);
		vector<vector<long long>> dp(n+1,vector<long long>(m+1,Max));
		for(int i=1;i<=n;i++)  
			cin>>a[i];
		for(int i=1;i<=m;i++)
			cin>>b[i];
		for(int i=1;i<=n;i++)
			pref[i]=pref[i-1]+a[i];
		
		for(int i=0;i<=m;i++)
			dp[0][i]=0;
			
			
		for(int j=1;j<=m;j++)
			for(int i=1;i<=n;i++)
			{
				dp[i][j]=dp[i][j-1];
				int g=Find(pref,i,b[j]);
				//cout<<"!"<<i<<' '<<j<<' '<<g<<endl;
				if(g!=i)
					dp[i][j]=min(dp[i][j],dp[g][j]+m-j);
			}
			
		
		if(dp[n][m]<Max)
			cout<<dp[n][m]<<endl;
		else
			cout<<-1<<endl;
	}

	return 0;
}


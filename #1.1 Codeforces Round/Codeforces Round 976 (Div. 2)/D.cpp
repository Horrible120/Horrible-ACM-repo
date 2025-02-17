#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

int t;

int getfa(vector<int> &fa,int x)
{
	if(fa[x]==x) return x;
	return x=getfa(fa,fa[x]);
}

void unite(vector<int> &fa,int x,int y)
{
	int a=getfa(fa,x),b=getfa(fa,y);
	if(a==b) return;
	fa[a]=b;
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	while(t--)
	{
		int n,m,ans=0;
		cin>>n>>m;
		
		vector<vector<int>> startcnt(n+1, vector<int>(11)),endcnt(n+1,vector<int>(11)),id(n+1,vector<int>(11));
		vector<int> fa(n+1);
		vector<vector<int>> dp(n+1,vector<int>(11));
		
		for(int i=1;i<=n;i++)
			fa[i]=i;
		for(int i=1;i<=10;i++)
			for(int j=1;j<=n;j++)
				id[j][i]=j;
		
		int a,d,k;
		for(int i=1;i<=m;i++)
		{
			cin>>a>>d>>k;
			startcnt[a][d]++;
			endcnt[a+k*d][d]++;
		}
		for(int j=1;j<=10;j++)
			for(int i=1;i<=n;i++)
			{
				dp[i][j]=startcnt[i][j]-endcnt[i][j];
				if(i>j&&dp[i-j][j])
				{
					unite(fa,i,i-j);
					dp[i][j]+=dp[i-j][j];
					//id[i][j]=id[i-j][j];
				}
			}
		
		for(int i=1;i<=n;i++)
			if(getfa(fa,i)==i)
				ans++;
		cout<<ans<<endl;
	}
	
	return 0;
}

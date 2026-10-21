#include<iostream>
#include<vector>
using namespace std;

int t;
const long long INF=1e18;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	int n,m;
	while(t--)
	{
		cin>>n>>m;
		
		long long ans=-INF; 
		
		vector<vector<long long>> v(n+10,vector<long long>(m+10));
		vector<vector<long long>> dpl(n+10,vector<long long>(m+10)),dpr(n+10,vector<long long>(m+10));
		vector<vector<long long>> pref(n+10,vector<long long>(m+10));
		vector<vector<long long>> prefn(n+10,vector<long long>(m+10)),suffx(n+10,vector<long long>(m+10));
		vector<vector<long long>> ppx(n+10,vector<long long>(m+10)),ssx(n+10,vector<long long>(m+10));
		
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
			{
				dpr[i][j]=-INF;
				dpl[i][j]=-INF;
			} 
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>v[i][j];
				
		for(int i=1;i<=n;i++)//预处理前缀和 
			for(int j=1;j<=m;j++)
				pref[i][j]=pref[i][j-1]+v[i][j];
				
		for(int i=1;i<=n;i++)//预处理前缀和的前缀最小值 & 后缀最大值 
		{
			for(int j=1;j<=m;j++)
				prefn[i][j]=min(pref[i][j],prefn[i][j-1]);
			suffx[i][m]=pref[i][m];
			for(int j=m-1;j>=1;j--)
				suffx[i][j]=max(pref[i][j],suffx[i][j+1]);
		}
		
		for(int j=m-1;j>=0;--j)//第一行特殊处理 
			dpl[1][j]=suffx[1][j+1]-pref[1][j];
        	
    	for(int j=1;j<=m;++j)//第一行特殊处理
			dpr[1][j]=pref[1][j]-prefn[1][j-1];
        
		for(int i=2;i<=n;i++)
		{
			//ppx[i][j]第 i-1 天选取2~j中的一个作为端点时，第 i 天的阶段最优（求出 之前的总收益减去最小前缀和 的最大值） 
			ppx[i][1]=max(dpr[i-1][1],dpl[i-1][1])-prefn[i][0];
			for(int j=2;j<=m;j++)
				ppx[i][j]=max(ppx[i][j-1],max(dpr[i-1][j],dpl[i-1][j])-prefn[i][j-1]);
				
			for(int j=2;j<=m;j++)
				dpr[i][j]=ppx[i][j-1]+pref[i][j];
			
		
			ssx[i][m-1]=max(dpr[i-1][m-1],dpl[i-1][m-1])+suffx[i][m];
			for(int j=m-2;j>=0;j--)
				ssx[i][j]=max(ssx[i][j+1],max(dpr[i-1][j],dpl[i-1][j])+suffx[i][j+1]);
				
			for(int j=m-2;j>=0;j--)
				dpl[i][j]=ssx[i][j+1]-pref[i][j];
		}
			
		
		for(int i=0;i<=m;i++)
			ans=max(ans,max(dpl[n][i],dpr[n][i]));
		
		/* 
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=m;j++)
				cout<<prefn[i][j]<<'|'<<suffx[i][j]<<"  ";
			cout<<endl;
		}
		cout<<endl;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=m;j++)
				cout<<ppx[i][j]<<'|'<<ssx[i][j]<<"  ";
			cout<<endl;
		}
		cout<<endl;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=m;j++)
				cout<<dpl[i][j]<<'|'<<dpr[i][j]<<"  ";
			cout<<endl;
		}
		*/
		cout<<ans<<endl;
	}
	
	return 0;
}
/*
1000
5 3
-36 34 -78
-12 -32 58
-83 64 45
-90 -81 -92
-95 47 -5
*/

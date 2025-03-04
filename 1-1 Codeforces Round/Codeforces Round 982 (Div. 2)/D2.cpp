#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef uint64_t ull;

const ll Mod=1e9+7,INF=1e18;

ll tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		ll n,m;
		cin>>n>>m;
		
		vector<ll> a(n+1),b(m+1),pre(n+1);
		
		for(int i=1;i<=n;i++)
			cin>>a[i],
			pre[i]=pre[i-1]+a[i];
		for(int i=1;i<=m;i++)
			cin>>b[i];
			
		ll r,ldp,lct,sum;
		vector<ll> dp(n+1,INF),cnt(n+1,0);
		
		//for(int i=1;i<=n;i++)
		//	cout<<pre[i]<<' ';
		dp[0]=0;
		cnt[0]=1;
		for(int i=1;i<=m;i++)
		{
			r=1,ldp=0,lct=0,sum=0;
			
			while(r<=n)
			{
				while(ldp<r&&pre[r]-pre[ldp]>b[i])
				{
					sum=(sum+Mod-cnt[ldp])%Mod;
					ldp++;
				}
				//if(ldp==r)
				//{
				//	r++;
				//	//cout<<"KKK";
				//	continue;
				//}
				if(lct<ldp)
				{
					sum=0;
					lct=ldp;
				}
				while(lct<r&&dp[lct]==dp[ldp])
				{
					sum=(sum+cnt[lct])%Mod;
					lct++;
				}
				if(ldp<r)
				{
					if(dp[r]==dp[ldp]+m-i)
						cnt[r]=(cnt[r]+sum)%Mod;
					else if(dp[r]>dp[ldp]+m-i)
					{
						//cout<<"KKK";
						cnt[r]=sum;
						dp[r]=dp[ldp]+m-i;
					}
				} 
				
				
				r++;
			}
		}
		if(dp[n]>=1e17)
			cout<<-1<<endl;
		else
			cout<<dp[n]<<' '<<cnt[n]<<endl;
		
	}

	return 0;
}



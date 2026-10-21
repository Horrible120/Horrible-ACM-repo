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

ll tt;
ll n;
const ll M=1e17;

void sv(vector<ll> &v,vector<ll> &pre,ll x,ll sub)
{
	v[x]-=sub;
	v[x+1]-=sub;
	
	if(x!=1)
	{
		pre[x+1]-=sub;
		pre[(x+2)%2+1]+=sub;
	}
	if(x!=n-1)
	{
		pre[x+2]+=sub;
		//if(x<n-3)
		//	pre[n-((x+1)%2)]-=sub;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		cin>>n;
		vector<ll> v(n+1),pre(n+1),ans(n+1);
		for(int i=1;i<=n;i++)
			cin>>v[i];
		
		if(n==1)
		{
			cout<<0<<endl;
			continue;
		}
			
		for(int i=1;i<=n/2+1;i++)
		{
			
			int a=i,b=n+1-i;
			
			if(v[a]>v[b])
			{
				sv(v,pre,a,v[a]-v[b]);
			}
			else
			{
				sv(v,pre,b-1,v[b]-v[a]);
			}
			
			
			
			if(i>1)
			{
				ll sub=v[i]-v[i-1];
				sv(v,pre,a,max(sub,0*1ll));
				sv(v,pre,b-1,max(sub,0*1ll));
			}
			
		}
		
		
		//---
		
		if(v[n/2+1]>v[n/2])
		{
			ll sub=v[n/2+1]-v[n/2];
			ll a=n/2,b=n/2+2;
			sv(v,pre,a,sub);
			sv(v,pre,a+1,sub);
		}
		
		
		for(int i=n/2;i>=1;i--)
		{
			ll sub=v[i]-v[i+1];
			ll ii=n+1-i;
			v[i]+=sub;
			v[ii]+=sub;
			pre[i+1]+=sub;
			if(ii+1<=n) pre[ii+1]-=sub;
		}
		
		
		
		ans[1]=pre[1];
		ans[2]=pre[2];
		for(int i=3;i<=n;i++)
			ans[i]=ans[i-2]+pre[i];
		for(int i=1;i<=n;i++)
			cout<<ans[i]+M<<' ';
		cout<<endl;
		
	}
	
	return 0;
}



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

bool check(vector<ll> &v,vector<ll> &up,ll n,ll mid)
{
	vector<ll> down(n+2);
	
	down[n+1]=mid;
	//cout<<"KKK"<<endl;
	for(int i=n;i>=1;i--)
	{
		if(down[i+1]<=v[i])
			down[i]=down[i+1]-1;
		else
			down[i]=down[i+1]+1;
	}
	
	for(int i=n;i>=1;i--)
		down[i]=min(down[i],down[i+1]);
	
	
	//cout<<"!!!"<<mid<<endl;
	//for(int i=1;i<=n;i++)
	//	cout<<up[i]<<' '<<down[i]<<endl;
	
	
	for(int i=0;i<=n-1;i++)
		if(up[i]>=down[i+2])
			return 1;
	return 0;	
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		ll n,ans=0,score=0;
		cin>>n;
		vector<ll> v(n+1),up(n+1);
		up[0]=0;
		
		for(int i=1;i<=n;i++)
			cin>>v[i];
		
		for(int i=1;i<=n;i++)
			if(v[i]>up[i-1])
				up[i]=up[i-1]+1;
			else if(v[i]<up[i-1])
				up[i]=up[i-1]-1;
			else
				up[i]=up[i-1];
		
		for(int i=1;i<=n;i++)
			up[i]=max(up[i-1],up[i]);
		
		ll l=0,r=300010,mid,flag;
		
		while(l<=r)
		{
			mid=(l+r)>>1;
			
			if(check(v,up,n,mid))
				score=mid,l=mid+1;
			else
				r=mid-1;
		} 
			
		cout<<score<<endl;
		
	}

	return 0;
}



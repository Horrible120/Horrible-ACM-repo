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

long long Max=1e18;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int n;
		cin>>n;
		long long ans=1e18,mx=1,subm=1,ti=0;
		vector<long long> v(n);
		
		set<long long> d;
		
		for(int i=0;i<n;i++)
			cin>>v[i];
		sort(v.begin(),v.end());
		//cout<<">>";
		if(n==1)
		{
			cout<<1<<endl;
			continue;
		}
		long long l[2010],r[2010];
		l[0]=1;
		r[0]=1;
		
		if(n%2)
		{
			for(int i=0;i<n;i+=2)
			{
				long long ns=0;
				for(int j=1;j<i;j+=2)
					ns=max(ns,v[j]-v[j-1]);
				//cout<<ns<<' ';
				for(int j=n-2;j>i;j-=2)
					ns=max(ns,v[j+1]-v[j]);
				//cout<<ns<<' ';
				ans=min(ans,ns);
			}
			cout<<ans<<endl;
		}
		else
		{
			for(int i=1;i<n;i+=2)
				mx=max(mx,v[i]-v[i-1]);
			cout<<mx<<endl;
		}
			
	}	

	return 0;
}


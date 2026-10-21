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

long long tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		int n;
		cin>>n;
		long long ans=1e18;
		vector<long long> v(n);
		for(int i=0;i<n;i++)
			cin>>v[i];
		sort(v.begin(),v.end());
		
		if(v[0]+v[1]>v[n-1])
		{
			cout<<0<<endl;
			continue;
		}
		int l=n-1;
		for(int i=n-1;i>=0;i--)
		{
			int hi=v[i];
			
			while(l>0&&hi<v[l]+v[l-1]) l--;
			
			//cout<<"!!!"<<l<<' '<<i<<endl;
			ans=min(ans,l+n-1ll-i);
		}
		
		//cout<<">>";
		cout<<ans<<endl;
	}

	return 0;
}



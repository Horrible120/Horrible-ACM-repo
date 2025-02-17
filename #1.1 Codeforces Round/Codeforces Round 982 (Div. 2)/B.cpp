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

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int n,ans=10000;
		cin>>n;
		vector<int> v(n+1),s(n);
		map<int,int> mp;
		for(int i=1;i<=n;i++)
		{
			cin>>v[i];
			s[i-1]=v[i];
			if(!mp[v[i]])
				mp[v[i]]=i;
		}
		sort(s.begin(),s.end(),cmp);
		
		for(int i=0;i<n;i++)
			ans=min(ans,mp[s[i]]-1+i);
		//cout<<">>";
		cout<<ans<<endl;
		
	}

	return 0;
}


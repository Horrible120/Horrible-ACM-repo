#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

int t;

int main()
{
	cin>>t;

	while(t--)
	{
		long long n,ans=0;
		cin>>n;
		
		multiset<long long> v;
		long long x;
		for(int i=0;i<n;i++)
		{
			cin>>x;
			v.insert(x);
		}
		//cout<<*(++v.begin())<<endl; 
		ans=*v.begin();
		for(auto i=++v.begin();i!=v.end();i++)
		{
			ans=(ans+*i)/2;
		}
		cout<<ans<<endl;	
	}
	
	return 0;
} 

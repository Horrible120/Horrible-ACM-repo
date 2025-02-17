#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int t;

bool cmp1(long long a,long long b)
{
	return a>b;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	long long sum,n,m;
	while(t--)
	{
		cin>>n>>m;
		
		sum=0;
		
		vector<long long> v(n);
		
		for(int i=0;i<n;i++)
			cin>>v[i];
			
		sort(v.begin(),v.end(),cmp1);
		
		for(auto &i:v)
			sum+=i;
		
		//for(auto &i:v)
		//	cout<<i<<endl;
		
		long long ans=max((sum+m-1)/m,*v.begin());
		
		cout<<ans<<endl;
		
		
	}
	
	return 0;
 } 

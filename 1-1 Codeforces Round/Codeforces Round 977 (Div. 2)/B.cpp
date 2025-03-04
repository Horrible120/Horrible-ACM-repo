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
		int n,x;
		cin>>n>>x;
		
		vector<int> v(n+3);
		
		int a;
		for(int i=0;i<n;i++)
		{
			cin>>a;
			if(a<=n) v[a]++; 
		}
		
		int i=0,ans=0;	
		for(int i=x;i<=n;i++)
			if(v[i-x])
				v[i]+=v[i-x]-1;
		for(int i=0;i<=n;i++)
			if(!v[i])
			{
				ans=i;
				break;
			}
		cout<<ans<<endl;
	}
	
	return 0;
} 

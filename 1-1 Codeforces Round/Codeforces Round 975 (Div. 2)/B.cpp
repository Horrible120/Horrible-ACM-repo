#include<iostream>
#include<vector>
#include<map>
using namespace std;

int t;

int main()
{
	cin>>t;
	
	while(t--)
	{
		long long n,q;
		cin>>n>>q;
		
		vector<long long> v(n);
		
		map<long long,long long> mp;
		
		for(int i=0;i<n;i++)
			cin>>v[i];
			
		if(n==2) mp[1]=v[1]-v[0]+1;
		else
		{
			mp[n-1]=2;
			for(long long i=1;i<n-1;i++)
			{
				if(mp[(i+1)*(n-i)-1])
				{
					long long tmp=mp[(i+1)*(n-i)-1];
					mp.erase((i+1)*(n-i)-1);
					mp[(i+1)*(n-i)-1]=tmp+1;
				}
				else
					mp[(i+1)*(n-i)-1]=1;
			}
			
			for(long long i=0;i<n-1;i++)
			{
				if(mp[(i+1)*(n-i-1)])
				{
					long long tmp=mp[(i+1)*(n-i-1)];
					mp.erase((i+1)*(n-i-1));
					mp[(i+1)*(n-i-1)]=tmp+v[i+1]-v[i]-1;
				}
				else
					mp[(i+1)*(n-i-1)]=v[i+1]-v[i]-1;
			}
		}
		
		long long qu=0;
		//cout<<"Ans:";
		for(int i=1;i<=q;i++)
		{
			cin>>qu;
			if(mp[qu]) cout<<mp[qu]<<' ';
			else cout<<0<<' ';
		}
		cout<<endl;
	}
	
	
	return 0;
 } 

#include<iostream>
#include<vector>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int t=0;
	
	cin>>t;
	
	while(t--)
	{
		long long n=0,mx=0,mxa=0;
		long long sum=0;
		cin>>n;
		vector<long long> a(n+1);
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
			if(a[i]>mx)
			{
				mx=a[i];
				mxa=i;
			}
		}
		
		if(n<=2)
		{
			cout<<"-1"<<endl;
			continue;
		}
		
		int ans=0;
			
		long long l=0,r=1000000000000;
		
		while(l<r-1)
		{
			long long mid=l+((r-l)>>1);
			int cpm=0;
			sum+=mid;
			a[mxa]+=mid;
			for(int i=1;i<=n;i++)
				if(a[i]*2*n<sum)
					cpm++;
			if(cpm*2>n)
				r=mid;
			else
				l=mid;
			sum-=mid;
			a[mxa]-=mid;
		}
		int cpm=0;
			sum+=l;
			a[mxa]+=l;
			for(int i=1;i<=n;i++)
				if(a[i]*2*n<sum)
					cpm++;
			if(cpm*2>n)
			{
				cout<<l<<endl; 
			}	
			else
			{
				cout<<r<<endl;
			}
	}
	
	return 0;
}

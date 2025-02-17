#include<iostream>
#include<vector>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	while(t--)
	{
		long long n,k;
		cin>>n>>k;
		
		long long maxn=0,sum=0;
		vector<long long> v(n);
		for(int i=0;i<n;i++)
		{
			cin>>v[i];
			sum+=v[i];
			maxn=max(maxn,v[i]);
		}
		
		for(long long i=n;i>=1;i--)
		{
			if((maxn*i-sum<=k&&maxn*i-sum>=0)||((i-(sum%i)<=k||sum%i==0)&&maxn*i-sum<0))
			{
				cout<<i<<endl;
				break;
			}
		}
		
	}
	
	return 0;
}

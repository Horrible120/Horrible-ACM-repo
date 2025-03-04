#include<iostream>
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
		int n,k,sum=0,ans=0;
		cin>>n>>k;
		
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			if(x>=k)
				sum+=x;
			if(x==0&&sum>0)
			{
				ans++;
				sum--;
			}		
		}
		cout<<ans<<endl;		
	}
	
	return 0;
}

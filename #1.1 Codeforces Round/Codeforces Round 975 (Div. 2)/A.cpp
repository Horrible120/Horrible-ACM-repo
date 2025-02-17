#include<iostream>
#include<vector>
using namespace std;

int t;

int main()
{
	cin>>t;
	
	while(t--)
	{
		int n;
		cin>>n;
		
		vector<int> v(n);
		
		int Max=0,tr=0,ans=0,dm=0;
		
		for(int i=0;i<n;i++)
		{
			cin>>v[i];
			Max=max(Max,v[i]);
		}
		for(int i=0;i<n;i+=2)
		{
			tr=max(tr,v[i]);
		}
		if(Max==tr||(n%2)==0)
			ans=Max+(n+1)/2;
		else
			ans=Max+n/2;
		cout<<ans<<endl;
	}
	
	
	return 0;
 } 

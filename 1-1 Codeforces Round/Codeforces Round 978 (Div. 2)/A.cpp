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
	
	int n,r,ansd,ans,anso;
	while(t--)
	{
		cin>>n>>r;
		ans=0;
		ansd=0;
		anso=0;
		vector<int> v(n+1);
		
		for(int i=1;i<=n;i++)
			cin>>v[i];
			
		for(int i=1;i<=n;i++)
		{
			ansd+=v[i]/2;
			ans+=v[i]%2;
		}
		anso=min(ansd,r)*2;
		if(r-min(ansd,r)>=ans)
			anso+=ans;
		else
			anso+=2*(r-min(ansd,r))-ans;
		cout<<anso<<endl;
	}
	
	return 0;
}

#include<iostream>
#include<vector>
#include<string>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	int n;
	while(t--)
	{
		string a,b;
		cin>>a>>b;
		
		int pre=0;
		
		while(pre<min(a.size(),b.size())&&a[pre]==b[pre])
			pre++;
		int ans=pre+(a.size()+b.size()-2*pre);
		
		if(pre) ans++;
		
		cout<<ans<<endl;
	}
	
	return 0;
}

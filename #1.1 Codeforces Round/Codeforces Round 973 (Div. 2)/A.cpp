#include<iostream>
using namespace std;

int t,n,x,y;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	for(int i=1;i<=t;i++)
	{
		cin>>n>>x>>y;
		if(x<=y)
			cout<<int((n+x-0.1)/x)<<endl;
		else
			cout<<int((n+y-0.1)/y)<<endl;
	}
	return 0;
}

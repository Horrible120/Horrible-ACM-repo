#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int t,n;
int a[100010];
int ans,g;

int gcd(int a,int b)
{
	int d=1;
	int c=0;
	while(d)
	{
		c=a/b;
		d=a%b;
		a=b;
		b=d;
	}
	return a;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	for(int i=1;i<=t;i++)
	{
		cin>>n;
		for(int j=1;j<=n;j++)
			cin>>a[j];
		g=a[1];
		ans=a[1];
		for(int j=2;j<=n;j++)
		{
			g=gcd(g,a[j]);
			ans+=g;
		}
		cout<<ans<<endl;
	} 
	
	return 0;
}

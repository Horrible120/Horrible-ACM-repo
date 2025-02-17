#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int t,n;
int a[200010];
long long ans;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	for(int i=1;i<=t;i++)
	{
		ans=0;
		cin>>n;
		for(int j=1;j<=n;j++)
			a[j]=[](){int x;cin>>x;return x;}();
			
		for(int j=1;j<n-1;j++)
			ans+=a[j];
		ans=a[n]-a[n-1]+ans;
		cout<<ans<<endl;
	}
	
	return 0;
}

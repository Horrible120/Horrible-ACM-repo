#include<iostream>
#include<vector>
using namespace std;

int n,c,ans,lst;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>c;
	
	vector<int> v(n+1);
	
	for(int i=1;i<=n;i++)
		cin>>v[i];
	
	ans=1;
	for(int i=2;i<=n;i++)
		if(v[i]-v[i-1]+lst<c)
			lst+=v[i]-v[i-1];
		else
			ans++,lst=0;
	
	cout<<ans<<endl;
	
	return 0;
}

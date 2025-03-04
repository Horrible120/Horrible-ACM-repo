#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

int t;

int SG(int a,int x)
{
	bool GB=0;
	int fa=0;
	for(int i=30;i>=0;i--)
	{
		if(x&(1<<i))
		{
			fa<<=1;
			if(a&(1<<i)||GB)
				fa+=1;
		}
		else if(a&(1<<i))
			GB=true;
	}
	
	for(int i=1;i<=30;i++)
		if(fa==(1<<i)-2)
			return 0;
		else if(fa==(1<<i)-1)
			return i;
		else if(fa==(1<<i))
			return i^1;
	
	for(int i=2;i<=30;i++)
		if(fa>(1<<i)&&fa<(2<<i)-2)
			return i+1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;
	
	//cout<<SG(6,t)<<endl;
	
	while(t--)
	{
		int n,xr=0;
		cin>>n;
		vector<int> v(n+1),a(n+1);
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>v[i];
		for(int i=1;i<=n;i++)
			xr^=SG(a[i],v[i]);
		if(xr)
			cout<<"Alice"<<endl;
		else
			cout<<"Bob"<<endl;
	}

	return 0;
}


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

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int x,y,k;
		cin>>x>>y>>k;
		int c=min(x,y);
		
		cout<<0<<' '<<0<<' '<<c<<' '<<c<<endl;
		cout<<0<<' '<<c<<' '<<c<<' '<<0<<endl;
	}

	return 0;
}


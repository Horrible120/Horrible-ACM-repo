#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	int a,b;
	while(t--)
	{
		cin>>a>>b;
		if(a>=b)
			cout<<a<<endl;
		else if(b<2*a)
			cout<<a-(b-a)<<endl;
		else
			cout<<0<<endl;
	}
	
	return 0;
}

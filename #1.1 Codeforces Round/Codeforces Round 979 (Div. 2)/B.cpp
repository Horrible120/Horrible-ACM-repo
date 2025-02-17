#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int t;

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	 
	int n;
	while(t--)
	{
		cin>>n;
		cout<<1;
		for(int i=2;i<=n;i++)
				cout<<0;
		cout<<endl;
	}
	
	return 0;
}

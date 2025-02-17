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
	
	while(t--)
	{
		int n;
		cin>>n;
		vector<int> v(n);
		for(int i=0;i<n;i++)
			cin>>v[i];
		sort(v.begin(),v.end());
		cout<<(n-1)*(v[n-1]-v[0])<<endl;
	}
	
	return 0;
}

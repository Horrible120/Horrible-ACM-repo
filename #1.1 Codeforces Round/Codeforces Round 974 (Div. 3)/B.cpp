#include<iostream>
using namespace std;

string solve(int n,int k)
{
	int x=0;
	if(n<=k)
	{
		x=(n+1)/2;
		if(x%2)
			return "NO";
		else
			return "YES";
	}
	else
	{
		x=(n+1)/2-(n-k+1)/2;
		if(x%2)
			return "NO";
		else
			return "YES";
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int t=0;
	
	cin>>t;
	
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		
		cout<<solve(n,k)<<endl;
				
	}
	
	return 0;
}

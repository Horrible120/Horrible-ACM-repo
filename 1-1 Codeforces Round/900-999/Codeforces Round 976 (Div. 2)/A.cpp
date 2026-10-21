#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

int t;

int solve(long long n,long long k)
{
	int ans=0;
	
	if(k==1) return n;
	
	while(n)
	{
		ans+=n%k;
		n/=k;
	}
	
	return ans;
}

int main()
{
	cin>>t;

	while(t--)
	{
		long long n,k;
		cin>>n>>k;
		
		cout<<solve(n,k)<<endl;
	}
	
	return 0;
} 

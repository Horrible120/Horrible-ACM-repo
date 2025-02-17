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
const long long M=1e9+7;

void solve(long long n,long long k)
{
	if(k==1)
	{
		cout<<n%M<<endl;
		return;
	}
	else
	{
		vector<long long> fib(6*k);
		fib[1]=1;
		fib[2]=1;
		long long ans=0,G=2;
		
		while(fib[G])
		{
			++G;
			fib[G]=(fib[G-1]+fib[G-2])%k;
			//if(G<5) cout<<fib[G];
		}
			
		cout<<(G*(n%M))%M<<endl;
	}
	
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		long long n,k;
		cin>>n>>k;
		solve(n,k); 
	}

	return 0;
}


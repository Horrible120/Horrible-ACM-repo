#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef uint64_t ull;

ll tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		ll n;
		cin>>n;
		vector<ll> v(n+1);
		ll flag=1;
		for(int i=1;i<=n;i++)
		{
			cin>>v[i];
			if(i>1)
				if(abs(v[i]-v[i-1])!=5&&abs(v[i]-v[i-1])!=7)
					flag=0;
		}
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}

	return 0;
}



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

bool cmp(ll a,ll b)
{
	return a>b;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		ll n,k,ans=0;
		cin>>n>>k;
		vector<ll> v(k);
		ll b,c;
		for(int i=1;i<=k;i++)
		{
			cin>>b>>c;
			v[b-1]+=c;
			//cout<<v[b-1]<<endl;
		}
		sort(v.begin(),v.end(),cmp);
		for(int i=0;i<min(n,k);i++)
			ans=ans+v[i];
		cout<<ans<<endl;
	}

	return 0;
}



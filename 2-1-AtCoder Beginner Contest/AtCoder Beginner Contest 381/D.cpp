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
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;



int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	ll n,ans=0,l,cnt=0;
	cin>>n;
	vector<ll> v(n+1),f(n+1);
	map<ll,ll> mp;
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	for(ll i=2;i<=n;i++){
		if(v[i]==v[i-1])
			f[i]=min(f[i-2]+2,i-mp[v[i]]);
		mp[v[i-1]]=i-1;
	}
	
	for(ll i=1;i<=n;i++)
		ans=max(ans,f[i]);
	
//	OOO
	cout<<ans<<endl;
	cout.flush();
	
	return 0;
}

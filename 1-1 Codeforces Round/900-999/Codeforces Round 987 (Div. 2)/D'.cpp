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

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;

struct DP{
	ll coo,h;
};

struct cmp1{
	const operator()(DP a,DP b) const{
		if(a.h!=b.h) return a.h>b.h;
		return a.coo>b.coo;
	}
};

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n;
		cin>>n;
		vector<ll> v(n+1),fa(n+1),dp(n+1),M(n+1);
		
		for(int i=1;i<=n;i++){
			fa[i]=i;
		}
		
		for(int i=1;i<=n;i++){
			cin>>v[i];
			M[i]=max(M[i-1],v[i]);
		}
		
		set<DP,cmp1> s;
		dp[n]=M[n];
		s.insert({n,v[n]});
		
		for(int i=n-1;i>=1;i--){
			if((s.upper_bound({i,M[i]}))!=s.end())
				dp[i]=max(M[i],dp[(*s.upper_bound({i,M[i]})).coo]);
			else
				dp[i]=M[i];
			s.insert({i,v[i]});
		}
//		cout<<">>";
		for(int i=1;i<=n;i++){
			cout<<dp[i]<<' ';
		}
		cout<<endl;
		
	}
	cout.flush();
	return 0;
}

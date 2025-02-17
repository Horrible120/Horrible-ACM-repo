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



int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,ans=0;
		cin>>n;
		vector<ll> cnt(n+1);
		ll x;
		for(int i=1;i<=n;i++){
			cin>>x;
			cnt[x]++;
		}
			
		for(int i=1;i<=n;i++)
			ans+=cnt[i]/2;
		cout<<ans<<'\n';
	}
	cout.flush();
	return 0;
}

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
	
	cin >> tt;
	
	while ( tt-- ) {
		ll ans=0;
		ll n;
		cin>>n;
		vector<pair<ll,ll>> v(n);
		
		for(ll i=0;i<n;i++) cin>>v[i].first;
		for(ll i=0;i<n;i++) cin>>v[i].second;
		
		ll mx=-INF;
		for(ll i=0;i<n;i++){
			auto [x,y]=v[i];
			ans+=max(x,y);
			mx=max(mx,min(x,y));
		}
		ans=ans+mx;
//		if(mx!=n-1){
//			ans=ans-max(v[n-1].first,v[n-1].second)+v[n-1].second;
//		}
//		OOO
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}

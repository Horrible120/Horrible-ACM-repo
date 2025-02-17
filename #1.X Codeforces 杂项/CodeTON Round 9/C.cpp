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
		ll x,m,ans=0;
		cin>>x>>m;
		ll k=log2(x)+2;
		vector<ll> cnt(x+1);
		
		
		
		for(ll i=1;i<=min(m,1ll<<k);i++){
			if(i!=x&&(x%(i^x)==0||i%(i^x)==0))
				ans++;
		}
		
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}

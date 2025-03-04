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
		ll n,k;
		cin>>n>>k;
		
		vector<ll> v;
		
		ll x;
		for(ll i=1;i<=n;i++){
			cin>>x;
			v.emplace_back(x);
		}
		sort(v.begin(),v.end(),greater<ll>());
//		OOO
		
		ll sum=0;
		for(auto it:v){
			sum+=it;
			if(sum>k){
				cout<<it+k-sum<<endl;
				break;
			}
		}
		if(sum<=k) cout<<k-sum<<endl;
	}
	
	cout.flush();
	
	return 0;
}

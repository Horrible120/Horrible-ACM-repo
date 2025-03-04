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
		ll n;
		cin>>n;
		vector<ll> v(n+1);
		
		for(ll i=1;i<=n;i++){
			cin>>v[i];
		}
		ll sum=0,ans=0;
		for(ll i=1;i<=n;i++){
			sum+=v[i];
			ll sq=sqrt(sum);
			if(sq*sq==sum){
				if(sq%2)
					ans++;
//				cout<<sum<<endl;
			}
		}
//		OOO
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}

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
		ll k;
		cin>>k;
		vector<ll> cnt(k+1);
		ll x;
		for(int i=1;i<=k;i++){
			cin>>x;
			cnt[x]++;
		}
		ll n=k-=2;
		for(int i=1;i<=sqrt(n)+1;i++){
			if(cnt[i]&&n%i==0){
				if(i!=n%i&&cnt[n/i])
					cout<<i<<' '<<n/i<<'\n';
				else if(i==n/i&&cnt[i]>=2)
					cout<<i<<' '<<i<<'\n';
				else
					continue;
				break;
			}
		}
	}
	cout.flush();
	return 0;
}

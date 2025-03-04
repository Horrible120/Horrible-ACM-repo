#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,sum{};
		cin>>n;
//		OOO
		vector<ll> v(n+1);
		for(ll i=1;i<=n;i++)
			cin>>v[i],sum+=v[i];
		if(sum%n){
			cout<<"NO"<<endl;
			continue;
		}
		ll ct=sum/n;
		sum=0;
		for(ll i=1;i<=n;i+=2)
			sum+=v[i];
		if(sum!=((n+1)/2)*ct){
			cout<<"NO"<<endl;
			continue;
		}
		sum=0;
		for(ll i=2;i<=n;i+=2)
			sum+=v[i];
		if(sum!=(n/2)*ct){
			cout<<"NO"<<endl;
			continue;
		}
		cout<<"YES"<<endl;
	}
	
	cout.flush();
	
	return 0;
}

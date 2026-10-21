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
		ll n,k;
		cin>>n>>k;
		vector<ll> a(n+1),ans(n+1);
		for(ll i=1;i<=n;i++) cin>>a[i];
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++){
				if(i!=j&&max(a[i]-a[j],a[j]-a[i])%k==0)
					ans[i]=-1;
			}
		for(ll i=1;i<=n;i++){
			if(ans[i]==0){
				cout<<"YES"<<endl<<i<<endl;
				break;
			}
			if(i==n) cout<<"NO"<<endl;
		}
	}
	
	cout.flush();
	
	return 0;
}

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
	
	vector<ll> v(31);
	v[0]=1;
	for(ll i=1;i<=30;i++)
		v[i]=2*(v[i-1]+1);
	
	
	while ( tt-- ) {
		ll n;
		cin>>n;
//		vector<ll> v(n+1);
//		for(ll i=1;i<=n;i++) cin>>v[i];
//		OOO
		for(ll i=0;i<=30;i++){
			if(n<=v[i]){
				cout<<i+1<<endl;
				break;
			}
		}
		
	}
	
	cout.flush();
	
	return 0;
}

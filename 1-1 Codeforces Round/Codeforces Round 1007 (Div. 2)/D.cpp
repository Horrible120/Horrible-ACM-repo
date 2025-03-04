#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,l,r;
	cin>>n>>l>>r;
	vector<ll> v(n+1),prev(n+1);
	for(ll i=1;i<=n;i++)
		cin>>v[i],prev[i]=prev[i-1]^v[i];
	ll ans=0;
	
	function<ll(ll)> sol=[&](ll k)->ll{
		if(k<=n) return v[k];
		if(k/2<=n) return prev[k/2];
		if(n&1){
			if(k/2&1)
				return prev[n];
			else
				return prev[n]^sol(k/2);
		}
		else{
			if(k/2&1)
				return sol(n+1)^prev[n];
			else
				return sol(n+1)^prev[n]^sol(k/2);
		}
	};
	
	cout<<sol(l)<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

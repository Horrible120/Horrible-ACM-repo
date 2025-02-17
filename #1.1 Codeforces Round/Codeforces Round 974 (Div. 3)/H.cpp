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

ll tt=1;
ull hs[1000010];

void solve(){
	ll n,q;
	cin>>n>>q;
	
	vector<ll> v(n+1);
	vector<ull> pre(n+1);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		pre[i]=pre[i-1]^hs[v[i]];
	}
	for(ll i=1;i<=q;i++){
		ll l,r;
		cin>>l>>r;
		if(!(pre[l-1]^pre[r])) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	for(ll i=1;i<=1000000;i++)
		hs[i]=rnd();
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

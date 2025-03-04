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

void solve(){
	ll n,sum=0,l=0;
	cin>>n;
	vector<ll> v(n+1),pre(n+1),sub(n+2);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		sum+=v[i];
	}
	for(ll i=1;i<=n;i++){
		pre[i]=pre[i-1]+v[i];
//		cout<<pre[i]<<' ';
	}
	for(ll i=n;i>=1;i--){
		sub[i]=sub[i+1]+v[i];
//		cout<<sub[i]<<' ';
	}
	for(ll i=1;i<=n;i++){
		if(v[i]==0&&sub[i]&&pre[i]) l=1;
	}
//	OOO
//	cout<<l<<"!";
	if(sum==0) cout<<0<<endl;
	else if(l) cout<<2<<endl;
	else cout<<1<<endl;
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

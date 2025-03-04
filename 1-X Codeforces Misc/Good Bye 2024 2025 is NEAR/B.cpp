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
	ll n;
	cin>>n;
	vector<ll> l(n+1),r(n+1);
	vector<ll> cnt(2*n+2,0),pre(2*n+2,0);
	for(ll i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		if(l[i]==r[i])
			cnt[l[i]]++;
	}
	for(ll i=1;i<=2*n+1;i++) pre[i]=pre[i-1]+(cnt[i]>0?0:1);
	
//	for(ll i=1;i<=2*n+1;i++) cout<<cnt[i]<<'|'<<pre[i]<<' ';cout<<endl;
	for(ll i=1;i<=n;i++){
		if(l[i]==r[i]){
			if(cnt[l[i]]>1) cout<<0;
			else cout<<1;
		}
		else{
			if(pre[r[i]]-pre[l[i]-1]>0) cout<<1;
			else cout<<0;
		}
	}
	cout<<endl;
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

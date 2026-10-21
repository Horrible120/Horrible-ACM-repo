#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> g(n+1);
	for(ll i=0;i<m;i++){
		ll u,v;
		cin>>u>>v;
		g[u].emplace_back(v);
	}
	vector<ll> d(n+1),ans;
	for(ll u=1;u<=n;u++){
		if(d[u]==2){
			ans.emplace_back(u);
			continue;
		}
		for(ll i=0;i<(ll)g[u].size();i++){
			ll v=g[u][i];
			d[v]=max(d[v],d[u]+1);
		}
	}
	cout<<ans.size()<<'\n';
	for(ll i=0;i<(ll)ans.size();i++) cout<<ans[i]<<' ';
	cout<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}

#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<pair<ll,ll>> eg[n+1];
	vector<ll> vis(n+1,0);
	ll ans=INF;
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg[u].emplace_back(v,w);
		eg[v].emplace_back(u,w);
	}
	function<void(ll,ll)> DFS=[&](ll u,ll dis){
		if(u==n){
			ans=min(ans,dis);
			return;
		}
		for(auto &[v,w]:eg[u]){
			if(!vis[v]){
				vis[v]=1;
				dis^=w;
				DFS(v,dis);
				dis^=w;
				vis[v]=0;
			}
		}
	};
	vis[1]=1;
	DFS(1,0);
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

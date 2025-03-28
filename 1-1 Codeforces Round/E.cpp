#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	v2ct<ll> eg(n+1,vector<ll>());
	vector<ll> col(n+1,0),v(n+1,0),fa(n+1,0),vis(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	for(ll i=1;i<=n-1;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	
	function<void(ll)> DFS=[&](ll u){
		vis[u]=1;
		for(auto v:eg[u]){
			if(!vis[v]){
				fa[v]=u;
				DFS(v);
			}
		}
	};
	
	DFS(1);
	
	ll bw=0,bb=0,ww=n,wb=0;
	
	auto shift=[&](ll u){
		if(col[u]==0){	//白
			if(u!=1)
		}
	}
	
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

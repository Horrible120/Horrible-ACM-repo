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
	ll n,st,en,tot=0;
	cin>>n>>st>>en;
	vector<ll> eg[n+1];
	vector<ll> dfn(n+1,0),rnk(n+1,0),son(n+1,0),fa(n+1,0);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	function<void(ll)> dfs=[&](ll u){
		dfn[u]=++tot;
		rnk[tot]=u;
		for(auto v:eg[u]){
			if(!dfn[v]){
				son[u]++;
				fa[v]=u;
				dfs(v);
			}
		}
	};
	
	dfs(en);
	
	vector<ll> vis(n+1,0);
	
	for(ll i=n;i>=1;i--)
		cout<<rnk[i]<<' ';
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

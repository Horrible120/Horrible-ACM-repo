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
	ll n,c;
	cin>>n>>c;
	vector<ll> eg[n+1],coin(n+1),dp1(n+1),dp0(n+1),vis(n+1);
	for(ll i=1;i<=n;i++){
		cin>>coin[i];
	}
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	function<void(ll)> DFS=[&](ll u)->void{
		dp1[u]=coin[u];
		vis[u]=true;
		for(auto v:eg[u]){
			if(!vis[v]){
				
				DFS(v);
				dp0[u]+=max(dp0[v],dp1[v]);
				dp1[u]+=max(dp0[v],dp1[v]-2*c);
			}
		}
	};
	
	DFS(1);
//	OOO
	cout<<max(dp1[1],dp0[1])<<endl;
	
	
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

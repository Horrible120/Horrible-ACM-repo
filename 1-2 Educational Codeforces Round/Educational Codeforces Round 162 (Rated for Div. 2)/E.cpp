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
	ll n,ans=0;
	cin>>n;
	vector<ll> v(n+1),vis(n+1,0);
	v2ct<ll> eg(n+1,vector<ll>());
	vector<map<ll,ll>> cnt(n+1,map<ll,ll>());
	
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>v[i];
	}
	for(ll i=1;i<n;i++){
		ll u,x;
		cin>>u>>x;
		eg[u].emplace_back(x);
		eg[x].emplace_back(u);
	}
	
	auto merge=[&](ll x,ll y)->void{
		if(cnt[x].size()<cnt[y].size())
			swap(cnt[x],cnt[y]);
		for(auto [u,ct]:cnt[y]){
			if(u!=v[x]) ans+=cnt[x][u]*ct;
			cnt[x][u]+=ct;
		}
	};
	
	function<void(ll)> DFS=[&](ll u){
		vis[u]=1;
		for(auto v:eg[u])
			if(!vis[v]){
				DFS(v);
				merge(u,v);
			}
		ans+=cnt[u][v[u]];
		cnt[u][v[u]]=1;
	};
	
	DFS(1);
//	OOO
	cout<<ans<<endl;
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

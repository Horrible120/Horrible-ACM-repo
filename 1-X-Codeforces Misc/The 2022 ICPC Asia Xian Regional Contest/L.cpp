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
	ll n;
	cin>>n;
	vector<vector<ll>> eg(n+1,vector<ll>());
	vector<ll> du(n+1,0);
	
	for(ll i=1;i<n;i++){
		ll u;
		cin>>u;
		eg[i+1].emplace_back(u);
		eg[u].emplace_back(i+1);
		du[i+1]++;
		du[u]++;
	};
	
	vector<ll> dep(n+1,0),cnt(n+1,0),vis(n+1,0);
	
	auto dfs=[&](auto &&self,ll u)->void{
		vis[u]=1;
		for(auto v:eg[u]) if(!vis[v]){
			self(self,v);
			dep[u]=max(dep[u],dep[v]+1);
		}
		cnt[dep[u]]++;
	};
	
	dfs(dfs,1);
	
//	for(ll i=0;i<=n;i++){
//		cout<<i<<' '<<cnt[i]<<endl;
//	}
	
	ll ans=INF;
	for(ll i=0;i<n;i++){
		ans=min(ans,cnt[i]+i);
	}
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
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

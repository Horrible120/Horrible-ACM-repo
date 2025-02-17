#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<ll> l(n+1),r(n+1),eg[n+1],vis(n+1),w(n+1);
	for(ll i=1;i<=n;i++){
		cin>>l[i]>>r[i];
	}
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	function<void(ll)> DFS=[&](ll x){
		vis[x]=1;
		ll tmp=0;
		vector<ll> son;
		for(auto it:eg[x]){
			if(vis[it]) continue;
			DFS(it);
			son.emplace_back(it);
			tmp=max(tmp,w[it]);
		}
		w[x]=min(r[x],max(l[x],tmp));
		for(auto it:son)
			ans+=max(w[it]-w[x],0ll);
	};
	DFS(1);
//	OOO
	cout<<ans+w[1]<<endl;
	
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

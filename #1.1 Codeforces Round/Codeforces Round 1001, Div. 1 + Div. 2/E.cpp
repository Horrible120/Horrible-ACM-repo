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
	ll n,cnt=0,ans=0;
	cin>>n;
	vector<ll> dfw(n+1),pre(n+1),suf(n+2);
	vector<ll> w(n+1),eg[n+1],vis(n+1),dfn(n+1),siz(n+1),book(n+1);
	
	for(ll i=1;i<=n;i++) cin>>w[i];
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	function<void(ll)> DFS=[&](ll x){
		vis[x]=1;
		siz[x]=1;
		dfn[x]=++cnt;
		for(auto it:eg[x]){
			if(vis[it]) continue;
			DFS(it);
			siz[x]+=siz[it];
		}
	};
	DFS(1);
	
	
	for(ll i=1;i<=n;i++) dfw[dfn[i]]=w[i];
	for(ll i=1;i<=n;i++) pre[i]=max(pre[i-1],dfw[i]);
	for(ll i=n;i>=1;i--) suf[i]=max(suf[i+1],dfw[i]);
	
//	OOO
//	for(ll i=1;i<=n;i++) cout<<suf[i]<<' ';cout<<endl;
	
	function<bool(ll)> check=[&](ll x){
		ll l=dfn[x],r=dfn[x]+siz[x]-1,tmp=0;
		tmp=max(tmp,max(pre[l-1],suf[r+1]));
		return tmp>w[x];
	};
	
	for(ll i=1;i<=n;i++)
		if(check(i))
			if(w[i]>w[ans])
				ans=i;
	
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

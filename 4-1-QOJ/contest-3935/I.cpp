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
	
	ll ans=0;
	
	vector<vector<ll>> sz(n+1,vector<ll>());
	
	for(ll i=1;i<=m;i++){
		ll k;
		cin>>k;
		for(ll j=1;j<=k;j++){
			ll x;
			cin>>x;
			sz[x].emplace_back(i);
		}
	}
	
	vector<vector<ll>> g(m+1,vector<ll>());
	
	vector<ll> cnt(m+1,0);
	
	for(ll i=1;i<=n;i++){
		if(sz[i].size()==1){
			cnt[sz[i][0]]++;
		} 
		else if(sz[i].size()==2){
			g[sz[i][0]].emplace_back(sz[i][1]);
			g[sz[i][1]].emplace_back(sz[i][0]);
//			cout<<"!!! "<<sz[i][0]<<' '<<sz[i][1]<<endl;
		}
	}
	
	vector<ll> tmp;
	
	vector<ll> vis(m+1,0);
	
	auto dfs=[&](this auto&& self,ll u)->void{
		vis[u]=1;
		tmp.emplace_back(u);
		for(auto v:g[u]){
			if(!vis[v]){
				self(v);
			}
		}
	};
	
	
	
	for(ll i=1;i<=m;i++){
		if(g[i].size()==1){
			cnt[i]++;
		}else if(g[i].size()>1){
			cnt[i]+=2;
		}
		
		if((!vis[i])&&(g[i].size()>1)){
			tmp.clear();
			dfs(i);
			
			ll flag=1;
			for(auto u:tmp){
				if(g[u].size()!=2) flag=0;
			}

			if(flag&&(ll)tmp.size()%2==1){
				ans--;
			}
		}
	}
	
	for(ll i=1;i<=m;i++) ans+=min(2ll,cnt[i]);
	
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

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
	vector<vector<pair<ll,ll>>> eg(n+1,vector<pair<ll,ll>>());
	
	for(ll i=1;i<n;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg[u].emplace_back(make_pair(v,w));
		eg[v].emplace_back(make_pair(u,w));
	}
	
	vector<array<ll,2>> dis(n+1,array<ll,2>());
	vector<ll> vis(n+1,0),fa(n+1,0),val(n+1,0),sum(n+1,0);
	
	ll ans=INF;
	
	auto dfs1=[&](this auto &&self,ll u)->void{
		vis[u]=1;
		for(auto [v,w]:eg[u]) if(!vis[v]){
			fa[v]=u;
			self(v);
			sum[u]+=dis[v][0]+w;
			if(dis[v][0]+w>dis[u][0]){
				dis[u][1]=dis[u][0];
				dis[u][0]=dis[v][0]+w;
			}else if(dis[v][0]+w>dis[u][1]){
				dis[u][1]=dis[v][0]+w;
			}
		}
		val[1]+=dis[u][0]*((ll)eg[u].size()-1)-sum[u];
	};
	
	
	
	dfs1(1);
	vis.assign(n+1,0);
	val[1]+=dis[1][0];
	
//	OOO cout<<endl;
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<dis[i][0]<<' '<<dis[i][1]<<endl;
//	}
	
	auto dfs2=[&](this auto &&self,ll u)->void{
		vis[u]=1;
		
		ans=min(ans,val[u]);
//		cout<<">>> "<<u<<' '<<val[u]<<endl;
		
		for(auto [v,w]:eg[u]) if(!vis[v]){
			val[v]=val[u]-(dis[v][0]*((ll)eg[v].size()-1)-sum[v])-(dis[u][0]*(ll)eg[u].size()-sum[u]);
			
			ll upd;
			
			if(dis[v][0]+w==dis[u][0]){
				val[v]+=dis[u][1]*((ll)eg[u].size()-1)-(sum[u]-dis[v][0]-w);
				upd=dis[u][1]+w;
			}else{
				val[v]+=dis[u][0]*((ll)eg[u].size()-1)-(sum[u]-dis[v][0]-w);
				upd=dis[u][0]+w;
			}
			
			if(upd>dis[v][0]){
				dis[v][1]=dis[v][0];
				dis[v][0]=upd;
			}else if(upd>dis[v][1]){
				dis[v][1]=upd;
			}
			sum[v]+=upd;
			val[v]+=dis[v][0]*(ll)eg[v].size()-sum[v];
			self(v);
		}
	};
	
	dfs2(1);
	
//	OOO cout<<endl;
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<dis[i][0]<<' '<<dis[i][1]<<endl;
//	}
	
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

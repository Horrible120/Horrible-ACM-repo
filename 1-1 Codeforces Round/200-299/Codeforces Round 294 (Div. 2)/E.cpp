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
	ll n,m;
	cin>>n;
	v2ct<ll> eg(n+1,vector<ll>());
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> dep(n+1,0),siz(n+1,0);
	v2ct<ll> fa(21,vector<ll>(n+1));
	
	auto DFS=[&](auto &&self,ll u)->void{
		siz[u]=1;
		for(auto v:eg[u]){
			if(!dep[v]){
				dep[v]=dep[u]+1;
				fa[0][v]=u;
				self(self,v);
				siz[u]+=siz[v];
			}
		}
	};
	
	dep[1]=1;
	DFS(DFS,1);
	
	for(ll i=1;i<=20;i++)
		for(ll j=1;j<=n;j++)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	
	auto get_lca=[&](ll u,ll v)->ll{
		if(dep[u]<dep[v])
			swap(u,v);
		ll del=dep[u]-dep[v],c=0;
		while(del){
			if(del&1){
				u=fa[c][u];
			}
			c++;
			del/=2;
		}
		
		if(u==v) return u;
		
		for(ll i=20;i>=0;i--){
			if(fa[i][u]!=fa[i][v]){
				u=fa[i][u];
				v=fa[i][v];
			}	
		}
		return fa[0][u];
	};
	
	auto get_k_fa=[&](ll u,ll k)->ll{
		ll del=k,c=0;
		while(del){
			if(del&1){
				u=fa[c][u];
			}
			c++;
			del/=2;
		}
		return u;
	};
	
	cin>>m;
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		ll lca=get_lca(u,v),ans=0;
		
//		OOO
		if(u==v){
			cout<<n<<endl;
		}
		else if((dep[u]+dep[v]-dep[lca]*2)&1){
			cout<<0<<endl;
		}
		else if(dep[u]-dep[lca]==dep[v]-dep[lca]){
			ll del=dep[u]-dep[lca]-1;
			ans=n-siz[get_k_fa(u,del)]-siz[get_k_fa(v,del)];
//			cout<<dep[lca]<<' '<<get_k_fa(u,del)<<' '<<get_k_fa(v,del)<<endl;
			cout<<ans<<endl;
		}
		else{
			if(dep[u]<dep[v])
				swap(u,v);
			ll del=(dep[u]+dep[v]-dep[lca]*2)/2;
			ans=siz[get_k_fa(u,del)]-siz[get_k_fa(u,del-1)];
			cout<<ans<<endl;
		}
	}
	
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

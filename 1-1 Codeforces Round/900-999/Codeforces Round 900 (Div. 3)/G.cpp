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
	
	vector<ll> val(n+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>val[i];
	
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<=n-1;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<vector<ll>> osum(n+1,vector<ll>(21,0)),nxt(n+1,vector<ll>(31,0)),fa(n+1,vector<ll>(21,0));
	
	vector<ll> vis(n+1,0),dep(n+1,0);
	
	auto DFS=[&](this auto &&self,ll u,ll f)->void{
		vis[u]=1;
		osum[u][0]=val[u];
		fa[u][0]=f;
		dep[u]=dep[f]+1;
		
		for(ll i=1;i<=18;i++){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			osum[u][i]=osum[u][i-1]|osum[fa[u][i-1]][i-1];
		}
		
		for(ll i=0;i<=30;i++){
			if(val[u]>>i&1){
				nxt[u][i]=u;
			}else if(u!=1){
				nxt[u][i]=nxt[f][i];
			}
		}
		
		for(auto v:eg[u]){
			if(!vis[v]){
				self(v,u);
			}
		}
	};
	
	DFS(1,0);
	
	ll q;
	cin>>q;
	
	auto glca=[&](ll u,ll v){
		if(dep[u]<dep[v]) swap(u,v);
		for(ll i=18;i>=0&&dep[u]>dep[v];i--){
			if(dep[u]-dep[v]>=(1<<i)){
				u=fa[u][i];
			}
		}
		
		if(u==v) return u;
		
		for(ll i=18;i>=0;i--){
			if(fa[u][i]!=fa[v][i]){
				u=fa[u][i];
				v=fa[v][i];
			}
		}
		
		return fa[u][0];
		
	};
	
	auto gsum=[&](ll s,ll t){
		ll res=0;
		for(ll i=18;i>=0;i--){
			if(dep[s]-dep[t]+1>=(1<<i)){
				res|=osum[s][i];
				s=fa[s][i];
			}
		}
		return res;
	};
	
	for(ll i=1;i<=q;i++){
		ll u,v;
		cin>>u>>v;
		ll w=glca(u,v);
		
//		cout<<w<<endl;
		
		ll ans=0;
		vector<ll> tmp;
		for(ll i=0;i<=30;i++){
			if(dep[nxt[u][i]]>=dep[w]){
				ans=max(ans,(ll)(__builtin_popcount(gsum(u,nxt[u][i]))+__builtin_popcount(gsum(nxt[u][i],w)|gsum(v,w))));
//				cout<<u<<' '<<i<<' '<<nxt[u][i]<<endl;
			}
			if(dep[nxt[v][i]]>=dep[w]){
				ans=max(ans,(ll)(__builtin_popcount(gsum(v,nxt[v][i]))+__builtin_popcount(gsum(nxt[v][i],w)|gsum(u,w))));
//				cout<<v<<' '<<i<<' '<<nxt[v][i]<<endl;
			}
		}
		cout<<ans<<' ';
	}
	cout<<endl;
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

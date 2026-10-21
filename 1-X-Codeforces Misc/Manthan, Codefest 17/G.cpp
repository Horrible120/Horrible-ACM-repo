#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<vector<ll>> eg(n+1);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> siz(n+1,0),sqz(n+1,0),tfa(n+1,0),dep(n+1,0);
	vector<ll> fa(n+1,0),ctb(n+1,0),sig(n+1,0),cnt(n+1,0);
	
	auto get_fa=[&](ll x){
		while(fa[x]!=x){
			x=fa[x]=fa[fa[x]];
		}
		return x;
	};
	
	auto merge=[&](ll x,ll y){
		ll fx=get_fa(x),fy=get_fa(y);
		
		if(fx==fy) return;
		if(cnt[fx]<cnt[fy]) swap(fx,fy);
//		cout<<"dsu "<<fx<<' '<<fy<<endl;
		
		if(dep[sig[fy]]<dep[sig[fx]]){
			cnt[sig[fy]]+=cnt[sig[fx]];
			sig[fx]=sig[fy];
		}else{
			cnt[sig[fx]]+=cnt[sig[fy]];
		}
		fa[fy]=fx;
	};
	
	auto DFS=[&](auto &&self,ll u)->void{
		siz[u]=1;
		sqz[u]=0;
		for(auto v:eg[u]) if(v!=tfa[u]){
			tfa[v]=u;
			dep[v]=dep[u]+1;
			self(self,v);
			siz[u]+=siz[v];
			sqz[u]+=siz[v]*siz[v];
		}
		ctb[u]=(n-1)*(n-1)-sqz[u]-(n-siz[u])*(n-siz[u]);
		ans+=ctb[u];
	};
	
	auto calc=[&](ll u,ll v){
//		vector<ll> tmp;
		ll ff;
		u=sig[get_fa(u)];
		v=sig[get_fa(v)];
		while(u!=v){
//			cout<<u<<' '<<v<<endl;
			if(dep[u]>=dep[v]){
				ans-=ctb[u];
				ctb[u]=0;
//				tmp.emplace_back(u);
				ff=sig[get_fa(tfa[u])];
				sqz[ff]+=sqz[u]-siz[u]*siz[u];
				merge(u,ff);
				u=ff;
			}else{
				ans-=ctb[v];
				ctb[v]=0;
//				tmp.emplace_back(v);
				ff=sig[get_fa(tfa[v])];
				sqz[ff]+=sqz[v]-siz[v]*siz[v];
				merge(v,ff);
				v=ff;
			}
		}
		
		ll lca=u;
		
		ans-=ctb[lca];
		ctb[lca]=0;
		
//		for(auto it:tmp){
//			merge(it,lca);
//		}
		
//		cout<<lca<<' '<<cnt[lca]<<' '<<sqz[lca]<<' '<<ans<<endl;
		
		ctb[lca]+=cnt[lca]*(cnt[lca]-1)*(cnt[lca]-2);
		ctb[lca]+=((n-cnt[lca])*(n-cnt[lca])-sqz[lca]-(n-siz[lca])*(n-siz[lca]))*cnt[lca];
		ctb[lca]+=cnt[lca]*(cnt[lca]-1)*(n-cnt[lca])*2;
		ans+=ctb[lca];
	};
	
	dep[1]=1;
	tfa[1]=1;
	DFS(DFS,1);
	
//	OOO
	cout<<ans<<endl;
	
	ll q;
	cin>>q;
	
	for(ll i=1;i<=n;i++){
		fa[i]=sig[i]=i;
		cnt[i]=1;
	}
	
	for(ll i=1;i<=q;i++){
		ll u,v;
		cin>>u>>v;
		calc(u,v);
//		OOO
		cout<<ans<<endl;
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

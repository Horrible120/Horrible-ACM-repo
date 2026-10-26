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
	vector<vector<pair<ll,ll>>> eg(n+1);
	for(ll i=1;i<n;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg[u].emplace_back(v,w);
		eg[v].emplace_back(u,w);
	}
	auto distance=[&](ll root)->vector<ll>{
		vector<ll> dis(n+1),par(n+1),ord;
		ord.emplace_back(root);
		for(ll i=0;i<(ll)ord.size();i++){
			ll u=ord[i];
			for(ll j=0;j<(ll)eg[u].size();j++){
				ll v=eg[u][j].first,w=eg[u][j].second;
				if(v==par[u])
					continue;
				par[v]=u;
				dis[v]=dis[u]+w;
				ord.emplace_back(v);
			}
		}
		return dis;
	};
	vector<ll> val=distance(1);
	ll a=max_element(val.begin()+1,val.end())-val.begin();
	val=distance(a);
	ll b=max_element(val.begin()+1,val.end())-val.begin();
	vector<ll> dis=distance(b);
	for(ll i=1;i<=n;i++)
		val[i]=max(val[i],dis[i]);
	ll root=min_element(val.begin()+1,val.end())-val.begin();

	vector<ll> fa(n+1),siz(n+1,1),son(n+1),ord;
	ord.emplace_back(root);
	for(ll i=0;i<(ll)ord.size();i++){
		ll u=ord[i];
		for(ll j=0;j<(ll)eg[u].size();j++){
			ll v=eg[u][j].first;
			if(v==fa[u])
				continue;
			fa[v]=u;
			ord.emplace_back(v);
		}
	}
	for(ll i=n-1;i>0;i--){
		ll u=ord[i],p=fa[u];
		siz[p]+=siz[u];
		if(!son[p]||siz[u]>siz[son[p]])
			son[p]=u;
	}

	vector<ll> path,delta(n+1);
	path.reserve(n);
	ll q;
	cin>>q;
	while(q--){
		ll lim,ans=0;
		cin>>lim;
		fill(delta.begin(),delta.end(),0);
		auto dfs=[&](this auto &&self,ll u)->void{
			ll base=path.size();
			while(u){
				path.emplace_back(u);
				ll p=lower_bound(path.begin(),path.end(),val[u]-lim,
					[&](ll x,ll v){return val[x]<v;})-path.begin();
				delta[u]++;
				if(p)
					delta[path[p-1]]--;
				for(ll i=0;i<(ll)eg[u].size();i++){
					ll v=eg[u][i].first;
					if(v!=fa[u]&&v!=son[u])
					self(v);
				}
				u=son[u];
			}
			path.resize(base);
		};
		dfs(root);
		for(ll i=n-1;i>=0;i--){
			ll u=ord[i];
			ans=max(ans,delta[u]);
			if(fa[u])
				delta[fa[u]]+=delta[u];
		}
		cout<<ans<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}

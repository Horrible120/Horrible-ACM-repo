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

vector<ll> ls,rs,dis,val;

ll merge(ll x,ll y){
	if(!x||!y) return x|y;
	if(val[x]<val[y]) swap(x,y);
	rs[x]=merge(rs[x],y);
	if(dis[ls[x]]<dis[rs[x]]) swap(ls[x],rs[x]);
	dis[x]=dis[rs[x]]+1;
	return x;
}

ll tt=1;

void solve(){
	ll n,q;
	cin>>n>>q;

	for(ll i=2,p;i<=n;i++) cin>>p;

	vector<ll> rt(n+1),fa(n+1),dep(n+1);
	ls.assign(q+1,0);
	rs.assign(q+1,0);
	dis.assign(q+1,0);
	val.assign(q+1,0);

	ll tot=0;
	for(ll i=0,u,v;i<q;i++){
		cin>>u>>v;
		if(v==1) continue;
		tot++;
		val[tot]=v;
		dis[tot]=1;
		rt[u]=merge(rt[u],tot);
	}

	for(ll u=n;u>=2;u--){
		if(!rt[u]){
			fa[u]=1;
			continue;
		}

		ll d=val[rt[u]];
		fa[u]=d;
		while(rt[u]&&val[rt[u]]==d){
			rt[u]=merge(ls[rt[u]],rs[rt[u]]);
		}
		rt[d]=merge(rt[d],rt[u]);
		rt[u]=0;
	}

	ll ans=0;
	for(ll u=2;u<=n;u++){
		dep[u]=dep[fa[u]]+1;
		ans+=dep[u];
	}
	cout<<ans<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
	}

	cout.flush();
	return 0;
}

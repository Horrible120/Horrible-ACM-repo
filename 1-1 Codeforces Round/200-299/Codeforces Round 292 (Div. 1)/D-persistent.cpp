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

	vector<ll> dfn(n+1);
	ll tim=0;
	auto dfs=[&](this auto &&self,ll u)->void{
		while(u){
			dfn[u]=++tim;
			for(ll i=0;i<(ll)eg[u].size();i++){
				ll v=eg[u][i].first;
				if(v!=fa[u]&&v!=son[u])
					self(v);
			}
			u=son[u];
		}
	};
	dfs(root);
	vector<ll> ids=ord,rt(n+1);
	sort(ids.begin(),ids.end(),[&](ll u,ll v){return val[u]<val[v];});
	vector<array<ll,3>> tr(1);
	tr.reserve(20*n+1);
	auto add=[&](this auto &&self,ll pre,ll l,ll r,ll x)->ll{
		ll p=tr.size();
		auto node=tr[pre];
		tr.emplace_back(node);
		tr[p][2]++;
		if(l==r)
			return p;
		ll mid=(l+r)/2;
		if(x<=mid)
			tr[p][0]=self(tr[pre][0],l,mid,x);
		else
			tr[p][1]=self(tr[pre][1],mid+1,r,x);
		return p;
	};
	auto query=[&](this auto &&self,ll p,ll l,ll r,ll ql,ll qr)->ll{
		if(!p)
			return 0;
		if(ql<=l&&r<=qr)
			return tr[p][2];
		ll mid=(l+r)/2,res=0;
		if(ql<=mid)
			res+=self(tr[p][0],l,mid,ql,qr);
		if(qr>mid)
			res+=self(tr[p][1],mid+1,r,ql,qr);
		return res;
	};
	for(ll i=0;i<n;i++)
		rt[i+1]=add(rt[i],1,n,dfn[ids[i]]);

	ll q;
	cin>>q;
	while(q--){
		ll lim,p=0,ans=0;
		cin>>lim;
		for(ll i=0;i<n;i++){
			ll u=ids[i];
			while(p<n&&val[ids[p]]<=val[u]+lim)
				p++;
			ans=max(ans,query(rt[p],1,n,dfn[u],dfn[u]+siz[u]-1));
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

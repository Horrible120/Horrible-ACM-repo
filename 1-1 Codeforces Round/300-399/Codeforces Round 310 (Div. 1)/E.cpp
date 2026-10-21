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
	ll n,m,q;
	cin>>n>>m>>q;
	vector<vector<pair<ll,ll>>> eg(n+1);
	vector<array<ll,2>> edge(m+1);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		edge[i]={u,v};
		eg[u].emplace_back(v,i);
		eg[v].emplace_back(u,i);
	}

	ll tim=0;
	vector<ll> dfn(n+1),low(n+1),par(n+1),eid(n+1),cur(n+1),cut(m+1),stk;
	for(ll i=1;i<=n;i++){
		if(dfn[i])
			continue;
		dfn[i]=low[i]=++tim;
		stk.emplace_back(i);
		while(!stk.empty()){
			ll u=stk[stk.size()-1];
			if(cur[u]==(ll)eg[u].size()){
				stk.pop_back();
				if(par[u]){
					ll p=par[u];
					low[p]=min(low[p],low[u]);
					if(low[u]>dfn[p])
						cut[eid[u]]=1;
				}
				continue;
			}

			auto [v,id]=eg[u][cur[u]++];
			if(id==eid[u])
				continue;
			if(dfn[v])
				low[u]=min(low[u],dfn[v]);
			else{
				par[v]=u;
				eid[v]=id;
				dfn[v]=low[v]=++tim;
				stk.emplace_back(v);
			}
		}
	}

	ll cnt=0;
	vector<ll> bel(n+1);
	for(ll i=1;i<=n;i++){
		if(bel[i])
			continue;
		bel[i]=++cnt;
		stk.emplace_back(i);
		while(!stk.empty()){
			ll u=stk[stk.size()-1];
			stk.pop_back();
			for(ll j=0;j<(ll)eg[u].size();j++){
				auto [v,id]=eg[u][j];
				if(cut[id]||bel[v])
					continue;
				bel[v]=cnt;
				stk.emplace_back(v);
			}
		}
	}

	vector<vector<ll>> tr(cnt+1);
	for(ll i=1;i<=m;i++){
		if(!cut[i])
			continue;
		ll u=bel[edge[i][0]],v=bel[edge[i][1]];
		tr[u].emplace_back(v);
		tr[v].emplace_back(u);
	}

	ll lg=1;
	while((1LL<<lg)<=cnt)
		lg++;
	vector<vector<ll>> fa(lg,vector<ll>(cnt+1));
	vector<ll> dep(cnt+1),rt(cnt+1),ord;
	for(ll i=1;i<=cnt;i++){
		if(rt[i])
			continue;
		rt[i]=i;
		dep[i]=1;
		ll pos=ord.size();
		ord.emplace_back(i);
		for(ll j=pos;j<(ll)ord.size();j++){
			ll u=ord[j];
			for(ll k=0;k<(ll)tr[u].size();k++){
				ll v=tr[u][k];
				if(v==fa[0][u])
					continue;
				fa[0][v]=u;
				dep[v]=dep[u]+1;
				rt[v]=i;
				for(ll p=1;p<lg;p++)
					fa[p][v]=fa[p-1][fa[p-1][v]];
				ord.emplace_back(v);
			}
		}
	}

	auto lca=[&](ll u,ll v){
		if(dep[u]<dep[v])
			swap(u,v);
		for(ll j=lg-1;j>=0;j--)
			if(dep[u]-dep[v]>=(1LL<<j))
				u=fa[j][u];
		if(u==v)
			return u;
		for(ll j=lg-1;j>=0;j--){
			if(fa[j][u]==fa[j][v])
				continue;
			u=fa[j][u];
			v=fa[j][v];
		}
		return fa[0][u];
	};

	bool ok=true;
	vector<ll> up(cnt+1),down(cnt+1);
	for(ll i=1;i<=q;i++){
		ll u,v;
		cin>>u>>v;
		u=bel[u];
		v=bel[v];
		if(rt[u]!=rt[v]){
			ok=false;
			continue;
		}
		ll z=lca(u,v);
		up[u]++;
		up[z]--;
		down[v]++;
		down[z]--;
	}

	for(ll i=(ll)ord.size()-1;i>=0;i--){
		ll u=ord[i],p=fa[0][u];
		if(!p)
			continue;
		if(up[u]>0&&down[u]>0)
			ok=false;
		up[p]+=up[u];
		down[p]+=down[u];
	}
	cout<<(ok?"Yes":"No")<<'\n';
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

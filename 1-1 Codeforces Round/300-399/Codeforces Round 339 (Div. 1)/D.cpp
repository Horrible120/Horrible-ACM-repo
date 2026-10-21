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
	vector<vector<ll>> eg(n+1),vt(n+1);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}

	ll lg=1;
	while((1ll<<lg)<=n)
		lg++;
	vector<vector<ll>> fa(n+1,vector<ll>(lg));
	vector<ll> dep(n+1),dfn(n+1),siz(n+1,1),ord;
	stack<ll> stk;
	stk.push(1);
	ll tot=0;
	while(!stk.empty()){
		ll u=stk.top();
		stk.pop();
		dfn[u]=++tot;
		ord.emplace_back(u);
		for(ll i=0;i<(ll)eg[u].size();i++){
			ll v=eg[u][i];
			if(v==fa[u][0])
				continue;
			fa[v][0]=u;
			dep[v]=dep[u]+1;
			for(ll j=1;j<lg;j++)
				fa[v][j]=fa[fa[v][j-1]][j-1];
			stk.push(v);
		}
	}
	for(ll i=n-1;i>=0;i--){
		ll u=ord[i];
		if(fa[u][0])
			siz[fa[u][0]]+=siz[u];
	}

	auto anc=[&](ll u,ll v){
		return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];
	};
	auto lca=[&](ll u,ll v){
		if(dep[u]<dep[v])
			swap(u,v);
		for(ll i=lg-1;i>=0;i--)
			if(dep[u]-dep[v]>=(1ll<<i))
				u=fa[u][i];
		if(u==v)
			return u;
		for(ll i=lg-1;i>=0;i--)
			if(fa[u][i]!=fa[v][i]){
				u=fa[u][i];
				v=fa[v][i];
			}
		return fa[u][0];
	};
	auto cmp=[&](ll u,ll v){
		return dfn[u]<dfn[v];
	};

	vector<ll> key(n+1),cost(n+1),f(n+1);
	ll q;
	cin>>q;
	while(q--){
		ll k;
		cin>>k;
		vector<ll> a(k);
		for(ll i=0;i<k;i++){
			cin>>a[i];
			key[a[i]]=1;
		}
		bool ok=true;
		for(ll i=0;i<k;i++)
			if(key[fa[a[i]][0]])
				ok=false;
		if(!ok){
			cout<<-1<<'\n';
			for(ll i=0;i<k;i++)
				key[a[i]]=0;
			continue;
		}

		sort(a.begin(),a.end(),cmp);
		vector<ll> ver=a;
		for(ll i=1;i<k;i++)
			ver.emplace_back(lca(a[i-1],a[i]));
		ver.emplace_back(1);
		sort(ver.begin(),ver.end(),cmp);
		ver.erase(unique(ver.begin(),ver.end()),ver.end());
		ll m=ver.size();
		for(ll i=0;i<m;i++)
			vt[ver[i]].clear();

		stack<ll> path;
		for(ll i=0;i<m;i++){
			ll u=ver[i];
			while(!path.empty()&&!anc(path.top(),u))
				path.pop();
			if(!path.empty())
				vt[path.top()].emplace_back(u);
			path.push(u);
		}

		for(ll i=m-1;i>=0;i--){
			ll u=ver[i],cnt=0;
			cost[u]=0;
			for(ll j=0;j<(ll)vt[u].size();j++){
				ll v=vt[u][j];
				cost[u]+=cost[v];
				cnt+=f[v];
			}
			if(key[u]){
				cost[u]+=cnt;
				f[u]=1;
			}
			else if(cnt>=2){
				cost[u]++;
				f[u]=0;
			}
			else
				f[u]=cnt;
		}
		cout<<cost[1]<<'\n';
		for(ll i=0;i<k;i++)
			key[a[i]]=0;
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

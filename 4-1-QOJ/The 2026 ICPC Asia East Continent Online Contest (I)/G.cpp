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

ull calc(const vector<ll>& a,const vector<ll>& b,ll C){
	if(a.size()>b.size()) return calc(b,a,C);
	ll n=a.size(),m=b.size(),lg=0;
	if(!n||!m||a[0]+b[0]>C) return 0;
	if(a[n-1]+b[m-1]<=C) return (ull)n*m;

	for(ll x=m;x;x>>=1) lg++;

	ull ans=0;
	if(n*lg<n+m){
		for(ll i=0;i<n;i++) ans+=upper_bound(b.begin(),b.end(),C-a[i])-b.begin();
	}else{
		ll j=m;
		for(ll i=0;i<n;i++){
			while(j&&a[i]+b[j-1]>C) j--;
			ans+=j;
		}
	}
	return ans;
}

void solve(){
	ll n,m,C;
	cin>>n>>m>>C;
	vector<ll> c(n+1);
	for(ll i=1;i<=n;i++) cin>>c[i];

	vector<vector<ll>> g(n+1),rg(n+1);
	vector<pair<ll,ll>> eg;
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		g[u].emplace_back(v);
		rg[v].emplace_back(u);
		eg.emplace_back(u,v);
	}
	if(n==1){
		cout<<(c[1]<=C)<<'\n';
		return;
	}

	auto bfs=[&](ll s,const vector<vector<ll>>& g){
		vector<ll> dis(n+1,-1);
		queue<ll> q;
		dis[s]=0;
		q.push(s);
		while(!q.empty()){
			ll u=q.front();
			q.pop();
			for(ll i=0;i<(ll)g[u].size();i++){
				ll v=g[u][i];
				if(dis[v]!=-1) continue;
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
		return dis;
	};

	auto ds=bfs(1,g),dt=bfs(n,rg);
	if(ds[n]==-1){
		cout<<0<<'\n';
		return;
	}

	vector<ll> ord;
	for(ll i=1;i<=n;i++){
		if(ds[i]!=-1&&dt[i]!=-1&&ds[i]+dt[i]==ds[n]) ord.emplace_back(i);
	}
	sort(ord.begin(),ord.end(),[&](ll u,ll v){
		return make_pair(ds[u],u)<make_pair(ds[v],v);
	});

	ll cnt=ord.size(),mid=cnt/2;
	vector<ll> bel(n+1,1),vl(n+1,0),vr(n+1,0);
	for(ll i=0;i<mid;i++) bel[ord[i]]=0;

	vector<vector<ll>> dag(n+1),rdag(n+1);
	vector<pair<ll,ll>> cut;
	for(ll i=0;i<m;i++){
		auto [u,v]=eg[i];
		if(ds[u]==-1||dt[v]==-1||ds[u]+1+dt[v]!=ds[n]) continue;
		dag[u].emplace_back(v);
		rdag[v].emplace_back(u);
		if(!bel[u]&&bel[v]){
			cut.emplace_back(u,v);
			vl[u]=vr[v]=1;
		}
	}

	vector<ull> f(n+1,0),h(n+1,0);
	f[1]=h[n]=1;
	for(ll i=0;i<cnt;i++){
		ll u=ord[i];
		for(ll j=0;j<(ll)dag[u].size();j++){
			ll v=dag[u][j];
			f[v]+=f[u];
		}
	}
	for(ll i=cnt-1;i>=0;i--){
		ll u=ord[i];
		for(ll j=0;j<(ll)rdag[u].size();j++){
			ll v=rdag[u][j];
			h[v]+=h[u];
		}
	}

	vector<vector<ll>> L(n+1),R(n+1);
	for(ll i=0;i<cnt;i++){
		ll u=ord[i];
		if(vl[u]) L[u].reserve(f[u]);
		if(vr[u]) R[u].reserve(h[u]);
	}

	auto dfs1=[&](auto&& self,ll u,ll sum)->void{
		if(sum>C) return;
		if(vl[u]) L[u].emplace_back(sum);
		for(ll i=0;i<(ll)dag[u].size();i++){
			ll v=dag[u][i];
			if(!bel[v]) self(self,v,sum+c[v]);
		}
	};
	auto dfs2=[&](auto&& self,ll u,ll sum)->void{
		if(sum>C) return;
		if(vr[u]) R[u].emplace_back(sum);
		for(ll i=0;i<(ll)rdag[u].size();i++){
			ll v=rdag[u][i];
			if(bel[v]) self(self,v,sum+c[v]);
		}
	};
	dfs1(dfs1,1,c[1]);
	dfs2(dfs2,n,c[n]);

	for(ll i=0;i<cnt;i++){
		ll u=ord[i];
		sort(L[u].begin(),L[u].end());
		sort(R[u].begin(),R[u].end());
	}
	ull ans=0;
	for(ll i=0;i<(ll)cut.size();i++){
		auto [u,v]=cut[i];
		ans+=calc(L[u],R[v],C);
	}
	cout<<ans<<'\n';
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

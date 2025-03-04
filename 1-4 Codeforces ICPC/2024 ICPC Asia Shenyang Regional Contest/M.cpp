#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"Yes"<<endl;	//输出宏
#define CN cout<<"No"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 5e14, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,q,tot=0,top=0,cnt=0;
	cin>>n>>m>>q;
	vector<pair<ll,ll>> eg[n+1];
	vector<ll> dfn(n+1),low(n+1),fa(n+1),instk(n+1),stk(n+1),vis(n+1),col(n+1),scc(n+1),good(n+1);
//	v2ct<ll> scc[n+1];
	
	function<void(ll)> DFS=[&](ll x){
		dfn[x]=++tot;
		low[x]=dfn[x];
		stk[++top]=x;
		instk[x]=1;
		vis[x]=1;
		for(auto [it,w]:eg[x]){
			if(!vis[it]) {
				DFS(it);
				low[x]=min(low[x],low[it]);
			}
			else if(instk[it])
				low[x]=min(low[x],dfn[it]);
		}
		if(dfn[x]==low[x]){
			scc[++cnt]=x;
			while(top>0&&low[stk[top]]>=low[x]){
				instk[stk[top]]=0;
				col[stk[top--]]=cnt;
			}
		}
	};
	
	for(ll i=1;i<=m;i++){
		ll u,w;
		cin>>u>>w;
//		cout<<"!!!"<<(u%n+n)%n<<' '<<((u+w)%n+n)%n<<endl;
		eg[(u%n+n)%n].emplace_back(((u+w)%n+n)%n,w);
	}
	
	for(ll i=0;i<n;i++)
		if(!vis[i]) DFS(i);
	
	
	vector<ll> dis(n+1);
	vis=vector<ll>(n+1,0);
	for(ll i=1;i<=cnt;i++){
		queue<ll> q;
		q.push(scc[i]);
		vis[scc[i]]=1;
		ll id=col[scc[i]];
		while(q.size()){
			ll u=q.front();q.pop();
			for(auto [v,w]:eg[u]){
				if(col[v]!=id) continue;
				if(!vis[v]){
					dis[v]=dis[u]+w;
					q.push(v);
					vis[v]=1;
				}
				else if(dis[v]!=dis[u]+w)
					good[id]=1;
			}
		}
	}
	
	vector<ll> reg[n+1];
	vis=vector<ll>(n+1,0);
	for(ll i=0;i<n;i++)
		for(auto [v,w]:eg[i])
			if(col[i]!=col[v])
				reg[col[i]].emplace_back(col[v]);
	
	function<void(ll)> DFS2=[&](ll x){
		vis[x]=1;
		for(auto v:reg[x]){
			if(!vis[v]) DFS(v);	
			good[x]|=good[v];
		}
	};
	
	for(ll i=1;i<=cnt;i++)
		if(!vis[i]) DFS2(i);

	for(ll i=1;i<=q;i++){
		ll x;
		cin>>x;
		if(good[col[(x%n+n)%n]]) CY
		else CN
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

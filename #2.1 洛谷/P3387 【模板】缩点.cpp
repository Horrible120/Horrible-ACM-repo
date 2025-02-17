#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

class H_map{
public:
	class Edge{
	public:
		ll to,w;
		Edge():to(0),w(0){}
		Edge(ll _to,ll _w):to(_to),w(_w){}
	};
	
	ll n,top,tot,cnt;
	v2ct<Edge> edge;
	vector<ll> instk,stk,dfn,low;
	vector<ll> col;
	v2ct<ll> scc;
	
	vector<ll> w,w2;
	
	H_map(){}
	
	H_map(ll _n){
		n=_n;
		top=tot=cnt=0;
		edge.assign(n+1,vector<Edge>());
		instk.assign(n+1,0);
		stk.assign(n+1,0);
		dfn.assign(n+1,0);
		low.assign(n+1,0);
		col.assign(n+1,0);
		scc.assign(1,vector<ll>());
		
		w.assign(n+1,0);
		w2.assign(n+1,0);
	}
	
	void add_dir_simple_edge(ll u,ll v){
		edge[u].emplace_back(v,1);}
	
	void add_undir_simple_edge(ll u,ll v){
		add_dir_simple_edge(u,v);
		add_dir_simple_edge(v,u);}
	
	void add_dir_edge(ll u,ll v,ll w){
		edge[u].emplace_back(v,w);}
	
	void add_undir_edge(ll u,ll v,ll w){
		add_dir_edge(u,v,w);
		add_dir_edge(v,u,w);}
	
	void DFS_Tarjan_SCC(ll u){
		stk[++top]=u;
		instk[u]=true;
		dfn[u]=low[u]=++tot;
		
		for(auto [v,w]:edge[u]){
			if(!dfn[v]){
				DFS_Tarjan_SCC(v);
				low[u]=min(low[u],low[v]);
			}
			else if(instk[v])
				low[u]=min(low[u],dfn[v]);
		}
		
		if(dfn[u]==low[u]){
			cnt++;
			scc.emplace_back(vector<ll>());
			while(top>0&&low[stk[top]]>=low[u]){
				w2[cnt]+=w[stk[top]];
				instk[stk[top]]=false;
				scc[cnt].emplace_back(stk[top]);
				col[stk[top--]]=cnt;
			}
		}
	}
	
	void Tarjan_SCC(){
		top=tot=cnt=0;
		instk.assign(n+1,0);
		stk.assign(n+1,0);
		dfn.assign(n+1,0);
		low.assign(n+1,0);
		col.assign(n+1,0);
		scc.assign(1,vector<ll>());
		
		for(ll i=1;i<=n;i++)
			if(!dfn[i])
				DFS_Tarjan_SCC(i);
	}
	
	void SCC_contract(H_map &res){
		
		Tarjan_SCC();
		res=H_map(cnt);
		for(ll i=1;i<=n;i++)
			for(auto [v,w]:edge[i])
				if(col[i]!=col[v])
					res.add_dir_edge(col[i],col[v],w);
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	H_map Map(n);
	
	for(ll i=1;i<=n;i++) cin>>Map.w[i];
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		Map.add_dir_simple_edge(u,v);
	}
	
	H_map Map2;
	Map.SCC_contract(Map2);
	
	vector<ll> vis(n+1),ans(n+1);
	function<void(ll)> DFS=[&](ll u){
		vis[u]=1;
		ans[u]=Map.w2[u];
		ll tmp=0;
		for(auto [v,w]:Map2.edge[u]){
			if(!vis[v]) DFS(v);
			tmp=max(tmp,ans[v]);
		}
		ans[u]+=tmp;
	};
	
//	CY
	
	ll y=0;
	for(ll i=1;i<=Map2.n;i++){
		if(!vis[i]) DFS(i);
		y=max(y,ans[i]);
//		cout<<Map.w2[i]<<endl;
	}
//	OOO
	cout<<y<<endl;
	
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

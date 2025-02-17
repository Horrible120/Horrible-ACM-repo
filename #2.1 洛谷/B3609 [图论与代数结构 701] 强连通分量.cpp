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
	
	void DFS_Tarjan(ll u){
		stk[++top]=u;
		instk[u]=true;
		dfn[u]=low[u]=++tot;
		for(auto [v,w]:edge[u]){
			if(!dfn[v]){
				DFS_Tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(instk[v])
				low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u]){
			cnt++;
			scc.emplace_back(vector<ll>());
			while(top>0&&low[stk[top]]>=low[u]){
				instk[stk[top]]=false;
				scc[cnt].emplace_back(stk[top]);
				col[stk[top--]]=cnt;
			}
		}
	}
	
	void Tarjan(){
		top=tot=cnt=0;
		instk.assign(n+1,0);
		stk.assign(n+1,0);
		dfn.assign(n+1,0);
		low.assign(n+1,0);
		col.assign(n+1,0);
		scc.assign(1,vector<ll>());
		for(ll i=1;i<=n;i++)
			if(!dfn[i])
				DFS_Tarjan(i);
		
		cout<<cnt<<endl;
		vector<ll> vis(cnt+1);
		for(ll i=1;i<=n;i++){
			if(vis[col[i]]) continue;
			vis[col[i]]=1;
			ll id=col[i];
			sort(scc[id].begin(),scc[id].end());
			for(auto it:scc[id])
				cout<<it<<' ';
			cout<<endl;
		}
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	H_map Map(n);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		Map.add_dir_simple_edge(u,v);
	}
	Map.Tarjan();
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

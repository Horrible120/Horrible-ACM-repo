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
	
	ll n,top,tot;
	ll cnt_SCC,cnt_eDCC,cnt_vDCC;
	v2ct<Edge> edge;
	vector<ll> instk,stk,dfn,low;
	vector<ll> col_SCC,col_eDCC;
	vector<ll> vcut,ecut,isvcut,isecut;
	v2ct<ll> SCC,vDCC;
	
	H_map(ll _n){
		n=_n;
		top=tot=0;
		cnt_SCC=cnt_eDCC=cnt_vDCC=0;
		edge.assign(n+1,vector<Edge>());
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
			cnt_SCC++;
			SCC.emplace_back(vector<ll>());
			while(top>0&&low[stk[top]]>=low[u]){
				instk[stk[top]]=false;
				SCC[cnt_SCC].emplace_back(stk[top]);
				col_SCC[stk[top--]]=cnt_SCC;
			}
		}
	}
	
	void Tarjan_SCC(){
		top=tot=cnt_SCC=0;
		instk.assign(n+1,0);
		stk.assign(n+1,0);
		dfn.assign(n+1,0);
		low.assign(n+1,0);
		col_SCC.assign(n+1,0);
		SCC.assign(1,vector<ll>());
		
		for(ll i=1;i<=n;i++)
			if(!dfn[i])
				DFS_Tarjan_SCC(i);
	}
	
	void SCC_contract(H_map &res){
		Tarjan_SCC();
		res=H_map(cnt_SCC);
		for(ll i=1;i<=n;i++)
			for(auto [v,w]:edge[i])
				if(col_SCC[i]!=col_SCC[v])
					res.add_dir_edge(col_SCC[i],col_SCC[v],w);
	}
	
	void DFS_Tarjan_vDCC(ll rt,ll u){
		stk[++top]=u;
		dfn[u]=low[u]=++tot;
		
		ll cnt_son=0;
		for(auto [v,w]:edge[u]){
			if(!dfn[v]){
				cnt_son++;
				DFS_Tarjan_vDCC(rt,v);
				low[u]=min(low[u],low[v]);
				
				if(low[v]>=dfn[u]){
					if((!isvcut[u])&&(u!=rt||cnt_son>1)){
						isvcut[u]=true;
						vcut.emplace_back(u);
					}
					cnt_vDCC++;
					vDCC.emplace_back(vector<ll>());
					
					do{
						vDCC[cnt_vDCC].emplace_back(stk[top--]);
					}while(vDCC[cnt_vDCC].back()!=v);
					
					vDCC[cnt_vDCC].emplace_back(u);
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
		
		if(u==rt&&cnt_son==0){
			cnt_vDCC++;
			vDCC.emplace_back(vector<ll>(1,u));
		}
	}
	
	void Tarjan_vDCC(){
		top=tot=cnt_vDCC=0;
		stk.assign(n+1,0);
		dfn.assign(n+1,0);
		low.assign(n+1,0);
		isvcut.assign(n+1,0);
		vcut.assign(0,0);
		vDCC.assign(1,vector<ll>());
		
		for(ll i=1;i<=n;i++)
			if(!dfn[i])
				DFS_Tarjan_vDCC(i,i);
		
	}
	
	void DFS_Tarjan_eDCC(ll u){
		
	}
	
};

void solve(){
	ll n,m;
	cin>>n>>m;
	H_map Map(n);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		Map.add_undir_simple_edge(u,v);
	}
	Map.Tarjan_vDCC();
	
	cout<<Map.vcut.size()<<endl;
	sort(Map.vcut.begin(),Map.vcut.end());
	for(auto it:Map.vcut)
		cout<<it<<' ';
	cout<<endl;
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

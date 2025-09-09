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
	ll cnt_SCC,cnt_eDCC,cnt_ecut,cnt_vDCC;
	v2ct<Edge> edge;
	vector<ll> instk,stk,dfn,low;
	vector<ll> col_SCC,col_eDCC;
	vector<ll> vcut,isvcut;
	v2ct<ll> SCC,vDCC,ecut,eDCC;
	
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
					do{vDCC[cnt_vDCC].emplace_back(stk[top--]);}while(vDCC[cnt_vDCC].back()!=v);
					vDCC[cnt_vDCC].emplace_back(u);
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
		
		if(u==rt)
			while(top>0){
				isvcut[u]=true;
				vcut.emplace_back(u);
				cnt_vDCC++;
				vDCC.emplace_back(vector<ll>(1,stk[top--]));
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
	
	void cDCC_contract(H_map &res,vector<ll> &reid){
		Tarjan_vDCC();
		ll _tot=cnt_vDCC;
		reid.assign(n+1,0);
		for(ll i=1;i<=n;i++)
			if(isvcut[i])
				reid[i]=++_tot;
		res=H_map(_tot);
		
		for(ll i=1;i<=cnt_vDCC;i++)
			for(auto v:vDCC[i])
				if(isvcut[v])
					add_undir_simple_edge(i,reid[v]);
		else
			reid[v]=i;
	}
	
	void cDCC_rebuild_RTT(H_map &res,vector<ll> &reid){	//点双重建圆方树
		
	}
	
	void DFS_Tarjan_eDCC(ll u,ll _fa){	//桥：要考虑重边
		stk[++top]=u;
		dfn[u]=low[u]=++tot;
		ll flag=false;
		for(auto [v,w]:edge[u]){
			if(!dfn[v]){
				DFS_Tarjan_eDCC(v,u);
				low[u]=min(low[u],low[v]);
				
				if(low[v]>dfn[u]){
					cnt_ecut++;	//这里需要注意 计数的时候记的是无向边的数量，实际上邻接表总共有 2n 对 (u,v)
					ecut[u].emplace_back(v);
					ecut[v].emplace_back(u);
				}
			}
			else if(v!=_fa||flag) low[u]=min(low[u],dfn[v]);
			else flag=true;
		}
		
		if(low[u]==dfn[u]){
			cnt_eDCC++;
			eDCC.emplace_back(vector<ll>());
			do{
				col_eDCC[stk[top]]=cnt_eDCC;
				eDCC[cnt_eDCC].emplace_back(stk[top--]);
			}while(eDCC[cnt_eDCC].back()!=u);
		}
	}
	
	void Tarjan_eDCC(){
		top=tot=cnt_eDCC=cnt_ecut=0;
		stk.assign(n+1,0);
		dfn.assign(n+1,0);
		low.assign(n+1,0);
		ecut.assign(n+1,vector<ll>());
		eDCC.assign(1,vector<ll>());
		col_eDCC.assign(n+1,0);
		
		for(ll i=1;i<=n;i++)
			if(!dfn[i])
				DFS_Tarjan_eDCC(i,0);
	}
	
	void eDCC_contract(H_map &res){
		Tarjan_eDCC();
		res=H_map(cnt_eDCC);
		for(ll i=1;i<=n;i++)
			for(auto [v,w]:edge[i])
				if(col_eDCC[i]!=col_eDCC[v])
					res.add_dir_edge(col_eDCC[i],col_eDCC[v],w);
	}
};

void solve(){
	ll n,m;
	cin>>n;
	H_map Map(n);
	
	vector<ll> a(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		Map.add_dir_simple_edge(u,v);
	}
	
	cin>>m;
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		Map.add_dir_simple_edge(u,v);
	}
	
	H_map newmap(1);
	Map.SCC_contract(newmap);
	
	
	
//	OOO
	
	vector<ll> sum(n+1,0);
	ll root=0;
	
	vector<ll> tvis(n+1,0);
	
	for(ll i=1;i<=Map.cnt_SCC;i++){
		for(auto [v,w]:newmap.edge[i]){
			tvis[v]=1;
		}
	}
	
	for(ll i=1;i<=Map.cnt_SCC;i++){
		if(!tvis[i]){
			root=i;
			cout<<"ROOT "<<root<<endl;
		}
	}
	
	for(ll i=1;i<=n;i++){
		sum[Map.col_SCC[i]]+=a[i];
	}
	
//	OOO
	
	vector<ll> vis(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cout<<i<<' '<<Map.col_SCC[i]<<' '<<sum[i]<<endl;
	}
	
	bitset<10001> nd[10001],ans;

	ans[0]=true;
	
	auto DFS=[&](auto &&self,ll u)->void{
		vis[u]=1;
		nd[u][0]=true;
		for(auto [v,w]:newmap.edge[u]){
			cout<<"EDGE "<<u<<' '<<v<<endl;
			if(!vis[v]){
				self(self,v);
				nd[u]|=nd[v];
//				sum[u]+=sum[v];
			}
		}
//		cout<<"!!! "<<u<<' '<<sum[u]<<endl;
		
		ans|=(nd[u]>>sum[u]);
	};
	
//	OOO
	
	DFS(DFS,root);
	
//	OOO
	
	cout<<ans.count()<<endl;
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

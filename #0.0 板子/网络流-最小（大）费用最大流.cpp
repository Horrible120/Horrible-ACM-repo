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

class H_cost_Flow{	//链式前向星存带费用网络
public:
	ll n,m;
	ll cntn=0,cnte=1;
	
	
	class Node{
	public:
		ll fir,cur;	//第一条边 当前弧优化中第一条未满流的边
		Node():fir(0),cur(0){}
	};
	
	class Edge{
	public:
		ll u,v,cap,w,flw,nxt;	//起点 终点 容量 流量 下一条边
		
		Edge():u(0),v(0),cap(0),w(0),flw(0){}
		Edge(ll _u,ll _v,ll _cap,ll _w,ll _flw,ll _nxt):u(_u),v(_v),cap(_cap),w(_w),flw(_flw),nxt(_nxt){}
	};
	
	vector<Node> node;
	vector<Edge> edge;
	vector<ll> dis,vis;
	
	void add_dir_edge(ll _u,ll _v,ll _cap,ll _w,ll _flw){	//创建单向边
		edge[++cnte]=Edge(_u,_v,_cap,_w,_flw,node[_u].fir);
		node[_u].fir=cnte;
	}
	
	void add_edge(ll _u,ll _v,ll _f,ll _w){	//建边（包含反向边）
		add_dir_edge(_u,_v,_f,_w,0);
		add_dir_edge(_v,_u,0,-_w,0);
	}
	
	H_cost_Flow(ll _n,ll _m){
		n=_n;
		m=_m;
		cntn=0;
		cnte=1;
		node.assign(n+1,Node());
		edge.assign(2*m+2,Edge());
		dis.assign(n+1,0);
		vis.assign(n+1,0);
	}
	
	bool SPFA(ll s,ll t){	//利用 SPFA 生成层次图
		queue<ll> q;
		dis.assign(n+1,INF);
		vis.assign(n+1,0);
		q.push(s); dis[s]=0; vis[s]=true;
		while(q.size()){
			ll u=q.front(); q.pop(); vis[u]=false;
			for(Edge e=edge[node[u].fir];e.u;e=edge[e.nxt]){
				ll v=e.v;
				if(e.cap>e.flw&&dis[v]>dis[u]+e.w){	//还可以增广 并且 可以松弛
					dis[v]=dis[u]+e.w;
					if(!vis[v]) q.push(v),vis[v]=true;
				}	
			}
		}
		return dis[t]!=INF;
	}
	
	ll DFS(ll u,ll flow,ll &cost,ll t){	// DFS 计算阻塞流 
		if(u==t||flow==0) return flow;
		ll ret=0;
		vis[u]=true;
		for(ll &i=node[u].cur;i;i=edge[i].nxt){
			Edge &e=edge[i],&oe=edge[i^1];
			ll v=e.v,d;
			if(dis[v]==dis[u]+e.w&&(!vis[v])&&
				(d=DFS(v,min(flow-ret,e.cap-e.flw),cost,t))){
				ret+=d;
				e.flw+=d;
				oe.flw-=d;
				cost+=d*e.w;
				if(ret==flow) return ret;
			}
		}
		vis[u]=false;
		return ret;
	}
	
	pair<ll,ll> Dinic(ll s,ll t){
		ll max_flow=0,min_cost=0;
		while(SPFA(s,t)){
			for(ll i=1;i<=n;i++) node[i].cur=node[i].fir;
			max_flow+=DFS(s,INF,min_cost,t);
		}
		return make_pair(max_flow,min_cost);
	}
	
private:
	
};

void solve(){
	ll n,m,s,t;
	cin>>n>>m>>s>>t;
	H_cost_Flow flow(n,m);
	for(ll i=1;i<=m;i++){
		ll u,v,f,w;
		cin>>u>>v>>f>>w;
		flow.add_edge(u,v,f,w);
	}
	auto [a,b]=flow.Dinic(s,t);
	cout<<a<<' '<<b<<endl;
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

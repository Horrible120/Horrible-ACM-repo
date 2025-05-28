#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

const ll INF = 4e18, Mod = 1e9+7;

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

class H_Map{	//链式前向星存带权图 类
public:
	ll n,m;
	ll cntn=0,cnte=1;
	
	class Node{	//图节点 类
	public:
		ll fir;	//首边
		Node():fir(0){}	//默认构造函数
	};
	
	class Edge{	//图有向边 类
	public:
		ll u,v,w,nxt;	//起点 终点 权值 下一条边
		
		Edge():u(0),v(0),w(0){}
		Edge(ll _u,ll _v,ll _w,ll _nxt):u(_u),v(_v),w(_w),nxt(_nxt){}
	};
	
	vector<Node> node;	//节点数组
	vector<Edge> edge;	//边数组
	
	void add_dir_edge(ll _u,ll _v,ll _w){	//加入有向边
		edge[++cnte]=Edge(_u,_v,_w,node[_u].fir);
		node[_u].fir=cnte;
	}
	
	void add_undir_edge(ll _u,ll _v,ll _w){	//加入无向边
		add_dir_edge(_u,_v,_w);
		add_dir_edge(_v,_u,_w);
	}
	
	vector<ll> SPFA(ll s){	//SPFA最短路  若有负环则返回全-INF序列
		vector<ll> dis(n+1,INF),cnt(n+1,0),in_que(n+1,INF);
		queue<ll> que;
		
		dis[s]=0,in_que[s]=1;
		que.push(s);
		
		while(!que.empty()){
			ll u=que.front();
			que.pop();
			in_que[u]=0;
			
			for(H_Map::Edge e=edge[node[u].fir];e.u;e=edge[e.nxt]){
				ll v=e.v,w=e.w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					cnt[v]=cnt[u]+1;
					if(cnt[u]>=n) return vector<ll>(n+1,-INF);
					if(!in_que[v]){
						que.push(v);
						in_que[v]=1;
					}
				}
			}
		}
		return dis;
	}
	
	vector<ll> Dijkstra(ll s){	//Dij最短路
		vector<ll> dis(n+1,INF),vis(n+1,0);
		std::priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> que;
		dis[s]=0;
		que.push(make_pair(0,s));
		while(!que.empty()){
			ll u=que.top().second;
			que.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(H_Map::Edge e=edge[node[u].fir];e.u;e=edge[e.nxt]){
				ll v=e.v,w=e.w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					que.push(make_pair(dis[v],v));
				}
			}
		}
		return dis;
	}
	
	ll opp(ll _eg){ return (_eg^1); }
	
	H_Map(ll _n,ll _m){	//初始化 图
		n=_n;
		m=_m;
		cntn=0;
		cnte=1;
		node.assign(n+1,Node());
		edge.assign(2*m+2,Edge());
	}
	
private:
	
};

class H_Flow{	//链式前向星存无费用网络
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
		ll u,v,cap,flw,nxt;	//起点 终点 容量 流量 下一条边
		
		Edge():u(0),v(0),cap(0),flw(0){}
		Edge(ll _u,ll _v,ll _cap,ll _flw,ll _nxt):u(_u),v(_v),cap(_cap),flw(_flw),nxt(_nxt){}
	};
	
	vector<Node> node;
	vector<Edge> edge;
	vector<ll> dis;
	
	void add_dir_edge(ll _u,ll _v,ll _cap,ll _flw){	//创建单向边
		edge[++cnte]=Edge(_u,_v,_cap,_flw,node[_u].fir);
		node[_u].fir=cnte;
	}
	
	void add_edge(ll _u,ll _v,ll _f){	//建边（包含反向边）
		add_dir_edge(_u,_v,_f,0);
		add_dir_edge(_v,_u,0,0);
	}
	
	H_Flow(ll _n,ll _m){
		n=_n;
		m=_m;
		cntn=0;
		cnte=1;
		node.assign(n+1,Node());
		edge.assign(2*m+2,Edge());
		dis.assign(n+1,0);
	}
	
	bool BFS(ll s,ll t){	//利用 BFS 生成层次图
		queue<ll> q;
		dis.assign(n+1,0);
		dis[s]=1;
		q.push(s);
		while(q.size()){
			ll u=q.front();
			q.pop();
			for(Edge e=edge[node[u].fir];e.u;e=edge[e.nxt]){
				ll v=e.v;
				if(dis[v]==0&&e.cap>e.flw){	//没访问过 并且 还可以增广
					dis[v]=dis[u]+1;
					q.push(v);
				}	
			}
		}
		return dis[t];
	}
	
	ll DFS(ll u,ll flow,ll t){	// DFS 计算阻塞流 
		if(u==t||flow==0) return flow;
		ll ret=0;
		for(ll &i=node[u].cur;i;i=edge[i].nxt){
			Edge &e=edge[i],&oe=edge[i^1];
			ll v=e.v,d;
			if(dis[v]==dis[u]+1&&
				(d=DFS(v,min(flow-ret,e.cap-e.flw),t))){
				ret+=d;
				e.flw+=d;
				oe.flw-=d;
				if(ret==flow) return ret;
			}
		}
		return ret;
	}
	
	ll Dinic(ll s,ll t){
		ll max_flow=0;
		while(BFS(s,t)){
			for(ll i=1;i<=n;i++) node[i].cur=node[i].fir;
			max_flow+=DFS(s,INF,t);
		}
		return max_flow;
	}
	
private:
	
};

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	
	H_Map mmap(n*m+2,(n+1)*(m+1)*2+1);
	
	ll s=n*m+1,t=n*m+2;
	
	H_Flow flow(n*m+2,(n+1)*(m+1)*2+1);
	
	for(ll i=1;i<=n;i++)
		mmap.add_undir_edge(s,(i-1)*m+1,0),
		mmap.add_undir_edge(t,i*m,0);
	
	v2ct<ll> d1(n+1,vector<ll>(m+1,0)),d2(n+1,vector<ll>(m+1,0));
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<m;j++){
			cin>>d1[i][j];
			mmap.add_undir_edge((i-1)*m+j,(i-1)*m+j+1,d1[i][j]);
		}
	}
	
	for(ll i=1;i<n;i++){
		for(ll j=1;j<=m;j++){
			cin>>d2[i][j];
			mmap.add_undir_edge((i-1)*m+j,i*m+j,d2[i][j]);
		}
	}
	
	ll pth=INF;
	
	vector sdis=mmap.Dijkstra(s);
	vector tdis=mmap.Dijkstra(t);
	
	for(ll i=1;i<=n;i++)
		pth=min(pth,tdis[(i-1)*m+1]);
	
	OOO
	cout<<" Pth: "<<pth<<endl;
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<m;j++){
			ll x=min(sdis[(i-1)*m+j]+tdis[(i-1)*m+j+1],tdis[(i-1)*m+j]+sdis[(i-1)*m+j+1])+d1[i][j];
			cout<<"!!! "<<i<<' '<<j<<' '<<x<<endl;
			if(i==1)
				flow.add_edge(s,(i-1)*(m-1)+j,max(0ll,k+pth-x));
			if(i==n)
				flow.add_edge((i-2)*(m-1)+j,t,max(0ll,k+pth-x));
			if(i>1&&i<n)
				flow.add_edge((i-2)*(m-1)+j,(i-1)*(m-1)+j,max(0ll,k+pth-x));
		}
	}
	
	for(ll i=1;i<n;i++){
		
		for(ll j=1;j<=m;j++){
			if(j==1||j==m)
				continue;
			
			ll x=min(sdis[(i-1)*m+j]+tdis[i*m+j],tdis[(i-1)*m+j]+sdis[i*m+j])+d2[i][j];
			cout<<"!!! "<<i<<' '<<j<<' '<<x<<endl;
			flow.add_edge((i-1)*(m-1)+j-1,(i-1)*(m-1)+j,max(0ll,k+pth-x));
		}
	}
	
	auto ans=flow.Dinic(s,t);
	
	OOO
	cout<<ans<<endl;
	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

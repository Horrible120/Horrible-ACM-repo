#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

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

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	H_Map rmap(n,m);
	
	vector<vector<pair<ll,ll>>> eg(n+1);
	
	for(ll i=1;i<=m;i++){
		ll u,v,l,r;
		cin>>u>>v>>l>>r;
		rmap.add_undir_edge(u,v,r);
		eg[u].emplace_back(v,l);
		eg[v].emplace_back(u,l);
	}
	
	auto disk=rmap.Dijkstra(k);
	
	vector<ll> vis(n+1,0),dis(n+1,INF);
	
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> que;
	dis[1]=-disk[1];
	que.push(make_pair(-disk[1],1));
	while(!que.empty()){
		auto [d,u]=que.top();
		que.pop();
		if(vis[u]) continue;
		if(dis[u]>=disk[u]) continue;
		vis[u]=1;
		for(auto [v,w]:eg[u]){
			if(dis[v]>max(d+w,-disk[v])){
				dis[v]=max(d+w,-disk[v]);
				que.push(make_pair(dis[v],v));
			}
		}
	}
	
	if(vis[n]){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	
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

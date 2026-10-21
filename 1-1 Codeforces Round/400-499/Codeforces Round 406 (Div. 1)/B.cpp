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
	ll n,q,s;
	cin>>n>>q>>s;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	H_Map Map(n*8+1,n*8+q*20+1);
	
	ll tot=n;
	
	vector<array<ll,2>> ch(n*8+1,array<ll,2>());
	
	auto build1=[&](this auto &&self,ll u,ll l,ll r)->void{	//
		if(l==r){
			Map.add_dir_edge(u,l,0);
			return;
		}
		ll mid=l+r>>1ll;
		ch[u][0]=++tot;
		Map.add_dir_edge(u,tot,0);
		self(tot,l,mid);
		ch[u][1]=++tot;
		Map.add_dir_edge(u,tot,0);
		self(tot,mid+1,r);
	};
	
	auto build2=[&](this auto &&self,ll u,ll l,ll r)->void{
		if(l==r){
			Map.add_dir_edge(l,u,0);
			return;
		}
		ll mid=l+r>>1ll;
		ch[u][0]=++tot;
		Map.add_dir_edge(tot,u,0);
		self(tot,l,mid);
		ch[u][1]=++tot;
		Map.add_dir_edge(tot,u,0);
		self(tot,mid+1,r);
	};
	
	auto add1=[&](this auto &&self,ll u,ll l,ll r,ll s,ll t,ll p,ll w){
		if(l>=s&&r<=t){
			Map.add_dir_edge(p,u,w);
			return;
		}
		ll mid=l+r>>1ll;
		if(mid>=s)
			self(ch[u][0],l,mid,s,t,p,w);
		if(mid<t)
			self(ch[u][1],mid+1,r,s,t,p,w);
	};
	
	auto add2=[&](this auto &&self,ll u,ll l,ll r,ll s,ll t,ll p,ll w){
		if(l>=s&&r<=t){
			Map.add_dir_edge(u,p,w);
			return;
		}
		ll mid=l+r>>1ll;
		if(mid>=s)
			self(ch[u][0],l,mid,s,t,p,w);
		if(mid<t)
			self(ch[u][1],mid+1,r,s,t,p,w);
	};
	
	ll rt[2];
	
	rt[0]=++tot;
	build1(rt[0],1,n);
	rt[1]=++tot;
	build2(rt[1],1,n);
	
	while(q--){
		ll op,u,v,l,r,w;
		cin>>op;
		if(op==1){
			cin>>u>>v>>w;
			Map.add_dir_edge(u,v,w);
		}else if(op==2){
			cin>>u>>l>>r>>w;
			add1(rt[0],1,n,l,r,u,w);
		}else{
			cin>>u>>l>>r>>w;
			add2(rt[1],1,n,l,r,u,w);
		}
	}
	auto dis=Map.Dijkstra(s);
	
	for(ll i=1;i<=n;i++){
		cout<<(dis[i]==INF?-1:dis[i])<<' ';
	}
	
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

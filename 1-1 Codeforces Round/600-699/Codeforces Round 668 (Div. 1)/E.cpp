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

		Edge():u(0),v(0),cap(0),flw(0),nxt(0){}
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
		if(u==t||flow==0)
			return flow;
		ll ret=0;
		for(ll &i=node[u].cur;i;i=edge[i].nxt){
			Edge &e=edge[i],&oe=edge[i^1];
			ll v=e.v,d;
			if(dis[v]==dis[u]+1&&
				(d=DFS(v,min(flow-ret,e.cap-e.flw),t))){
				ret+=d;
				e.flw+=d;
				oe.flw-=d;
				if(ret==flow)
					return ret;
			}
		}
		return ret;
	}

	ll Dinic(ll s,ll t){
		ll max_flow=0;
		while(BFS(s,t)){
			for(ll i=1;i<=n;i++)
				node[i].cur=node[i].fir;
			max_flow+=DFS(s,INF,t);
		}

		return max_flow;
	}

private:

};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<string> a(n+2,string(m+2,'.'));
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		a[i]="."+a[i]+".";
	}

	vector<vector<ll>> hor(n+2,vector<ll>(m+2)),ver(n+2,vector<ll>(m+2));
	ll blk=0,cnt=0;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			if(a[i][j]=='#'){
				blk++;
				if(a[i][j+1]=='#')
					hor[i][j]=++cnt;
				if(a[i+1][j]=='#')
					ver[i][j]=++cnt;
			}

	ll s=cnt+1,t=cnt+2;
	H_Flow flow(cnt+2,cnt+4*blk);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			if(a[i][j]=='#'){
				if(hor[i][j])
					flow.add_edge(s,hor[i][j],1);
				if(ver[i][j])
					flow.add_edge(ver[i][j],t,1);

				ll h[2]={hor[i][j-1],hor[i][j]};
				ll v[2]={ver[i-1][j],ver[i][j]};
				for(ll x=0;x<2;x++)
					for(ll y=0;y<2;y++)
						if(h[x]&&v[y])
							flow.add_edge(h[x],v[y],1);
			}

	cout<<blk-cnt+flow.Dinic(s,t)<<'\n';
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

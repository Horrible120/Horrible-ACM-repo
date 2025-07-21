#include <bits/stdc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏
//#pragma GCC optimize(3,"Ofast","inline")

using namespace std;

mt19937_64 rnd( time( 0 ) );
typedef int ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

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
		dis=vector<ll>(n+1,INF);
		vis=vector<ll>(n+1,0);
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
	ll n,s=1,t=2,cnt=2;
	cin>>n;
	vector<ll> a(n+1),fct(4e4+1,0),np(4e4+1),pr(4e4+1),prm,pfct(1e6+1);
	map<ll,ll> id;
	
	for (ll i = 2; i <= 4e4; i++) {
		if (!np[i]) {
			fct[i] = 1;
			pr[i] = i;			//素数在最小素因子是他本身
			prm.emplace_back(i);
		}
		for (auto j : prm) {
			if (j * i > 4e4) break;
			np[i *j] = 1;
			pr[i *j] = j;
			if (i % j == 0) {
				fct[i *j] = fct[i]+1;
				break;
			}
			fct[i *j] = fct[i]+1;
		}
	}
	
//	for(ll i=1;i<=100;i++) cout<<i<<' '<<fct[i]<<endl;
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		if(!id[a[i]]) id[a[i]]=++cnt;
		for(ll j=1;j*j<=a[i];j++)
			if(a[i]%j==0){
				if(!id[j]) id[j]=++cnt;
				if(!id[a[i]/j]) id[a[i]/j]=++cnt;
			}
	}
	
	H_cost_Flow flow(cnt+10,2e6);
	vector<ll> afct[301];
	
	for(int i=1;i<=n;i++)
		flow.add_edge(s,id[a[i]],1,0);
	
	for(ll i=1;i<=n;i++){
		ll _x=a[i],u=id[a[i]];
		
		if(pfct[u]==0){
			for(auto it:prm){	//统计每个编号的素因子数
				if(_x%it==0) afct[i].emplace_back(it);
				while(_x%it==0&&_x>1){
					pfct[u]++;
					_x/=it;
				}
			}
			if(_x>1){
				pfct[u]++;
				afct[i].emplace_back(_x);
			}
		}
		else{
			for(auto it:prm){	//统计每个编号的素因子数
				if(_x%it==0) afct[i].emplace_back(it);
				while(_x%it==0&&_x>1)
					_x/=it;
			}
			if(_x>1)
				afct[i].emplace_back(_x);
		}
		
		
		for(ll j=1;j*j<=a[i];j++)
			if(a[i]%j==0){
				ll _x=j,u=id[j];
				if(pfct[u]==0){
					for(auto it:afct[i]){	//统计每个编号的素因子数
						while(_x%it==0&&_x>1){
							pfct[u]++;
							_x/=it;
						}
					}
				}
				
				if(a[i]!=j*j){
					ll _x=a[i]/j,u=id[a[i]/j];
					if(pfct[u]==0){
						for(auto it:afct[i]){	//统计每个编号的素因子数
							while(_x%it==0&&_x>1){
								pfct[u]++;
								_x/=it;
							}
						}
					}
				}
			}
		
	}
	
	for(auto [x,u]:id){
		flow.add_edge(u,t,1,0);
//		ll _x=x;
//		for(auto it:prm){	//统计每个编号的素因子数
//			while(_x%it==0){
//				pfct[u]++;
//				_x/=it;
//				if(_x<4e4){
//					pfct[u]+=fct[_x];
//					_x=1;
//					break;
//				}
//				if(_x==1) break;
//			}
//		}
//		if(_x>1) pfct[u]++;
	}
	
//	for(ll i=1;i<=n;i++){
//		ll u=id[a[i]];
//		for(ll j=1;j*j<=a[i];j++)
//			if(a[i]%j==0){
//				flow.add_edge(u,id[j],1,-(pfct[u]-pfct[id[j]]));
//				if(a[i]!=j*j) flow.add_edge(u,id[a[i]/j],1,-(pfct[u]-pfct[id[a[i]/j]]));
//			}
//	}
	
	for(int i=1;i<=n;i++){
		vector<pair<ll,ll>> tmp;
		for(auto &[x,u]:id)
			if(!(a[i]%x)) tmp.emplace_back(make_pair(-(pfct[id[a[i]]]-pfct[u]),u));
		sort(tmp.begin(),tmp.end());
		
		for(ll j=0;j<=min(n-1,(ll)(tmp.size()-1));j++){	//小优化：对于每个a[i],只取前n个
			auto [w,u]=tmp[j];
			flow.add_edge(id[a[i]],u,1,w);
		}
	}	
	
	cout<<-flow.Dinic(s,t).second<<endl;
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

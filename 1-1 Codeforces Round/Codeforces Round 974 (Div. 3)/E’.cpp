#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt,n,m,h;

struct Node{
	ll dis[2]={INF,INF},vis[2]={0,0},fir,num;
};

struct cmp0{
	operator()(const Node a,const Node b) const{
		if(a.dis[0]^b.dis[0]) return a.dis[0]<b.dis[0];
		else return a.num<b.num;
	}
};

struct cmp1{
	operator()(const Node a,const Node b) const{
		if(a.dis[1]^b.dis[1]) return a.dis[1]<b.dis[1];
		else return a.num<b.num;
	}
};

struct Edge{
	ll u,v,w,next;
};

void add_edge(vector<Node> &node,vector<Edge> &edge,ll u,ll v,ll w,ll key){
	edge[key].u=u;
	edge[key].v=v;
	edge[key].w=w;
	edge[key].next=node[u].fir;
	node[u].fir=key;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		cin>>n>>m>>h;
		vector<Node> node(2*(n+1));
		vector<Edge> edge(4*m+2*h+1);
		
		for(ll i=1;i<=2*n;i++)
			node[i].num=i;
		
		ll x,y,w,tot=0;
		for(ll i=1;i<=h;i++){
			cin>>x;
			add_edge(node,edge,x,x+n,0,++tot);
			add_edge(node,edge,x+n,x,0,++tot);
		}
		
		for(ll i=1;i<=m;i++){
			cin>>x>>y>>w;
			add_edge(node,edge,x,y,w,++tot);
			add_edge(node,edge,y,x,w,++tot);
			
			add_edge(node,edge,y+n,x+n,w/2,++tot);
			add_edge(node,edge,x+n,y+n,w/2,++tot);
		}
		
		
//		for(ll i=1;i<=2*n;i++){
//			OOO cout<<i<<':'<<endl;
//			for(Edge e=edge[node[i].fir];e.u;e=edge[e.next])
//				cout<<e.u<<' '<<e.v<<' '<<e.w<<endl;
//		}
		
		
		{//人工作用域，便于后续定义同名 set
		set<Node,cmp0> s;
		node[1].dis[0]=0;
		s.insert(node[1]);
		while(s.size()){
			Node &cur=node[(*s.begin()).num];
			s.erase(s.begin());
			
			if(cur.vis[0]) continue;	
			else cur.vis[0]=1;
			
			for(Edge e=edge[cur.fir];e.u;e=edge[e.next])
				if(cur.dis[0]+e.w<node[e.v].dis[0]){
					node[e.v].dis[0]=cur.dis[0]+e.w;
					s.insert(node[e.v]);
				}
		}}
		
		{//人工作用域，便于后续定义同名 set
		set<Node,cmp1> s;
		node[n].dis[1]=0;
		s.insert(node[n]);
		while(s.size()){
			Node &cur=node[(*s.begin()).num];
			s.erase(s.begin());
			
			if(cur.vis[1]) continue;	
			else cur.vis[1]=1;
			
			for(Edge e=edge[cur.fir];e.u;e=edge[e.next])
				if(cur.dis[1]+e.w<node[e.v].dis[1]){
					node[e.v].dis[1]=cur.dis[1]+e.w;
					s.insert(node[e.v]);
				}
		}}
		
		ll ans=INF;
		for(ll i=1;i<=n;i++)
			ans=min(ans,max(min(node[i].dis[0],node[i+n].dis[0]),min(node[i].dis[1],node[i+n].dis[1])));
		
//		OOO OOO cout<<endl;
//		for(ll i=1;i<=n;i++)
//			cout<<node[i].dis[0]<<'|'<<node[i+n].dis[0]<<endl;
		
//		OOO OOO OOO OOO
		if(ans==INF)
			cout<<-1<<endl;
		else
			cout<<ans<<endl;
		
	}
	
	cout.flush();
	
	return 0;
}

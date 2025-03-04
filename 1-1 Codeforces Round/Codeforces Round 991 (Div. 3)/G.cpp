#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt,tot,n;

struct Node{
	ll fir,key,son,kkk;
	bool vis;
	Node (){
		fir=0;
		key=0;
		son=0;
		vis=0;
		kkk=0;
	}
};
struct Edge{
	ll u,v,next;
	Edge (){
		u=v=0;
		next=0;
	}
};

Node node[200010];
Edge edge[400010];

void add_edge(ll u,ll v){
	edge[++tot].u=u;
	edge[tot].v=v;
	edge[tot].next=node[u].fir;
	node[u].fir=tot;
}

void init(){
	tot=0;
	for(ll i=1;i<=n;i++)
		node[i]=Node{};
	for(ll i=1;i<=2*n;i++)
		edge[i]=Edge{};
	
}

void DFS(ll x){
	Node &cur=node[x];
	cur.vis=1;
	
	for(Edge e=edge[cur.fir];e.u;e=edge[e.next]){
		if(node[e.v].vis) continue;
		cur.son++;
		DFS(e.v);
	}
}

void solve(ll x){
	Node &cur=node[x];
	cur.vis=1;
	cur.key=cur.son;
	vector<ll> tmp;
	for(Edge e=edge[node[x].fir];e.u;e=edge[e.next]){
		if(node[e.v].vis) continue;
		solve(e.v);
		tmp.emplace_back(node[e.v].key);
		cur.key=max(cur.key,node[e.v].key+cur.son-1);
	}
	
	sort(tmp.begin(),tmp.end(),greater<ll>());
	
	if(tmp.size()>=2)
		cur.kkk=cur.son-(x==1?2:1)+tmp[0]+tmp[1];
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		cin>>n;
		init();
		ll u,v;
		for(ll i=1;i<n;i++){
			cin>>u>>v;
			add_edge(u,v);
			add_edge(v,u);
		}
		DFS(1);
//		for(ll i=1;i<=n;i++) cout<<node[i].son<<' ';
		
		for(ll i=1;i<=n;i++) node[i].vis=0;
		solve(1);
		ll ans=0;
//		cout<<"!!!SON";
//		for(ll i=1;i<=n;i++) cout<<node[i].key<<' ';
//		cout<<endl;
		
		for(ll i=1;i<=n;i++){
			ans=max(ans,node[i].key+(i==1?0:1));
			ans=max(ans,node[i].kkk);
		}
//		OOO
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}

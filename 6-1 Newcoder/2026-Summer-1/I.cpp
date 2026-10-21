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

struct DSU{
	vector<int> fa,siz;
	DSU(int n):fa(n+1),siz(n+1,1){
		iota(fa.begin(),fa.end(),0);
	}
	int find(int x){
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return 0;
		if(siz[x]<siz[y]) swap(x,y);
		fa[y]=x;
		siz[x]+=siz[y];
		return 1;
	}
};

void solve(){
	int n,m;
	cin>>n>>m;
	vector<ll> x(n+1);
	for(int i=1;i<=n;i++) cin>>x[i];
	
	vector<array<int,2>> e(m+1),ans(m+1);
	DSU d(n),nd(n);
	
	for(int i=1;i<=m;i++){
		auto &[u,v]=e[i];
		cin>>u>>v;
		if(x[u]==x[v]) d.merge(u,v);
	}
	
	vector<int> bel(n+1);
	for(int i=1;i<=n;i++) bel[i]=d.find(i);
	
	vector<vector<int>> g(n+1);
	vector<vector<pair<int,int>>> tr(n+1);
	int extra=0;
	
	for(int i=1;i<=m;i++){
		auto [u,v]=e[i];
		int a=bel[u],b=bel[v];
		
		if(a==b){
			g[u].push_back(v);
			g[v].push_back(u);
		}else if(nd.merge(a,b)){
			tr[a].push_back({b,i});
			tr[b].push_back({a,i});
		}else if(!extra) extra=i;
	}
	
	if(!extra){
		cout<<"No\n";
		return;
	}
	
	vector<int> rt(n+1);
	
	auto orient=[&](int id,int c){
		auto [u,v]=e[id];
		if(bel[u]!=c) swap(u,v);
		ans[id]={u,v};
		rt[c]=u;
	};
	
	int s=bel[e[extra][0]];
	orient(extra,s);
	
	queue<int> q;
	vector<int> vis(n+1);
	vis[s]=1;
	q.push(s);
	
	while(q.size()){
		int u=q.front();
		q.pop();
		
		for(auto [v,id]:tr[u]){
			if(vis[v]) continue;
			vis[v]=1;
			orient(id,v);
			q.push(v);
		}
	}
	
	for(int i=1;i<=m;i++)
		if(bel[e[i][0]]!=bel[e[i][1]]&&!ans[i][0])
			ans[i]=e[i];
	
	vector<int> dfn(n+1);
	int tim=0;
	
	for(int i=1;i<=n;i++){
		if(bel[i]!=i) continue;
		
		queue<int> que;
		dfn[rt[i]]=++tim;
		que.push(rt[i]);
		
		while(que.size()){
			int u=que.front();
			que.pop();
			
			for(int v:g[u]){
				if(dfn[v]) continue;
				dfn[v]=++tim;
				que.push(v);
			}
		}
	}
	
	for(int i=1;i<=m;i++){
		auto [u,v]=e[i];
		if(bel[u]!=bel[v]) continue;
		if(dfn[u]<dfn[v]) swap(u,v);
		ans[i]={u,v};
	}
	
	cout<<"Yes\n";
	for(int i=1;i<=m;i++)
		cout<<ans[i][0]<<' '<<ans[i][1]<<'\n';
}

int main(){
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

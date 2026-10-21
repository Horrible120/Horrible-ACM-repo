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

void solve(){
	ll n,m,p,b;
	cin>>n>>m>>p>>b;
	
	vector<ll> nd(n+1,0),vb,vp,vis(n+1,0),dis(n+1,INF),du(n+1,0),cnt(n+1,0);
	vector<vector<ll>> edge(n+1);
	
	for(ll i=1;i<=p;i++){
		ll x;
		cin>>x;
		vp.emplace_back(x);
	}
	
	for(ll i=1;i<=b;i++){
		ll x;
		cin>>x;
		vb.emplace_back(x);
		nd[x]=1;
	}
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		edge[u].emplace_back(v);
		edge[v].emplace_back(u);
		if(nd[u]==1&&nd[v]==1){
			du[u]++;
			du[v]++;
		}
	}
	
	ll tot=0;
	for(auto u:vp){
		for(auto v:edge[u]){
			if(nd[v]==1){
				if(du[v]) cnt[u]=n;
				else cnt[u]=max(1ll,cnt[u]);
			}
		}
		tot+=cnt[u];
	}
	
	queue<ll> que;
	que.push(1);
	vis[1]=1;
	dis[1]=0;
	while(que.size()){
		ll u=que.front();
		que.pop();
		for(auto v:edge[u]){
			dis[v]=min(dis[v],dis[u]+1);
			if((!vis[v])&&nd[v]==1){
				que.push(v);
				vis[v]=1;
			}
		}
	}
	
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<dis[i]<<endl;
//	}
	
	ll flag=0;
	for(auto u:vp){
		if(dis[u]-1ll<=tot-cnt[u]){
			flag=1;
		}
	}
	
	if(flag){
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

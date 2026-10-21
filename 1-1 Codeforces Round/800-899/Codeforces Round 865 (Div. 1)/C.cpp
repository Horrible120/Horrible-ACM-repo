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

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[v].emplace_back(u);
	}
	
	
	
	vector<ll> ti(n+1,INF);
	ti[1]=1;
	
	vector<ll> vis(n+1,0);
	
	queue<ll> que;
	
	que.push(1);
	vis[1]=1;
	
	while(que.size()){
		ll u=que.front();
		que.pop();
		for(auto v:eg[u]){
			ti[v]=min(ti[v],ti[u]+1);
			if(!vis[v]){
				vis[v]=1;;
				que.push(v);
			}
		}
	}
	
	ll ans=0;
	for(ll i=1;i<=n;i++) if(ti[i]<INF) ans+=ti[i]; else {cout<<"INFINITE"<<endl;return;}
	
	
	
	cout<<"FINITE"<<endl;
	cout<<ans<<endl;
	
	vector<vector<ll>> cnt(n+1,vector<ll>());
	
	for(ll i=1;i<=n;i++) if(ti[i]<INF) cnt[ti[i]].emplace_back(i);
	
	for(ll i=n;i>=1;i--){
		for(ll j=i;j<=n;j+=2){
			for(auto it:cnt[j]){
				cout<<it<<' ';
			}
		}
	}
	
	for(ll i=2;i<=n;i++){
		for(ll j=i;j<=n;j+=2){
			for(auto it:cnt[j]){
				cout<<it<<' ';
			}
		}
	}
	
	
}

int main() {
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

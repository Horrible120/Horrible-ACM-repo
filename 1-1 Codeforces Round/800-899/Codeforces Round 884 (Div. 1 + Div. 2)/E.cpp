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
	ll n,m,k;
	cin>>n>>m>>k;
	vector<vector<pair<ll,ll>>> eg(n+m+1,vector<pair<ll,ll>>());
	
	for(ll i=1;i<=k;i++){
		ll u[2],v[2];
		cin>>u[0]>>v[0]>>u[1]>>v[1];
		if(u[1]-u[0]==v[1]-v[0]){
			eg[min(u[0],u[1])].emplace_back(make_pair(min(v[0],v[1])+n,1));
			eg[min(v[0],v[1])+n].emplace_back(make_pair(min(u[0],u[1]),1));
		}else{
			eg[min(u[0],u[1])].emplace_back(make_pair(min(v[0],v[1])+n,0));
			eg[min(v[0],v[1])+n].emplace_back(make_pair(min(u[0],u[1]),0));
		}
	}
	
	vector<ll> col(n+m+1,0),vis(n+m+1,0);
	
	auto DFS=[&](this auto &&self,ll u)->void{
		vis[u]=1;
		for(auto [v,c]:eg[u]) {
			col[v]=col[u]^c;
			if(!vis[v]) self(v);
		}
	};
	
	for(ll i=1;i<=n+m;i++){
		if(!vis[i]){
			DFS(i);
		}
	}
	
	ll flag=0;
	
	for(ll i=1;i<=n;i++){
		for(auto [v,c]:eg[i]) {
			if((col[v]^col[i])!=c)
				flag=1;
		}
	}
	
	if(flag){
		cout<<"No"<<endl;
	}else{
		cout<<"Yes"<<endl;
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

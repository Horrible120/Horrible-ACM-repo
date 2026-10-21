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
	ll n;
	cin>>n;
	vector<ll> a(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> vis(n+1,0),f(n+1,0);
	vector<set<ll>> st(n+1);
	
	auto DFS=[&](this auto &&self,ll u)->void{
		vis[u]=1;
		
		map<ll,ll> mp;
		
		if(eg[u].size()==1&&u!=1){
			st[u].insert(a[u]);
			return;
		}
		
		for(auto v:eg[u]) if(!vis[v]){
			a[v]^=a[u];
			self(v);
			f[u]+=f[v]+1;
			if(st[v].size()>st[u].size()) swap(st[u],st[v]);
			for(auto it:st[v]){
				if(st[u].count(it)) mp[it]++;
				else st[u].insert(it);
			}
		}
		
		ll mx=0;
		
		if(!mp.empty()){
//			cout<<"!!!"<<endl;
			for(auto [it,cnt]:mp) mx=max(mx,cnt);
			st[u].clear();
			for(auto [it,cnt]:mp) if(cnt==mx) st[u].insert(it);
			
		}
		
		
		
		f[u]-=mx+1;
		
//		cout<<u<<' '<<a[u]<<' '<<f[u]<<endl;
	};
	
	DFS(1);
	
	if(st[1].count(0)){
		cout<<f[1]<<endl;
	}else{
		cout<<f[1]+1<<endl;
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

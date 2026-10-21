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
	ll n,q;
	cin>>n>>q;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	vector<array<ll,400>> dp(n+1,array<ll,400>());
	
	vector<ll> val(n+1,0),dep(n+1,0),fa(n+1,0),vis(n+1,0),cnt(n+1,0),rnk(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>val[i];
	}
	
	for(ll i=2;i<=n;i++){
		ll x;
		cin>>x;
		eg[x].emplace_back(i);
		fa[i]=x;
	}
	
	auto dfs=[&](auto &&self,ll u)->void{
		dep[u]=dep[fa[u]]+1;
		for(auto v:eg[u]){
			self(self,v);
		}
		rnk[u]=++cnt[dep[u]];
	};
	
	dfs(dfs,1);
	
	auto sol=[&](auto &&self, ll x,ll y)->ll{
		if(x==1) return val[1]*val[1];
		
		if(cnt[dep[x]]>=400) return val[x]*val[y]+self(self,fa[x],fa[y]);
		
		if(dp[x][rnk[y]]) return dp[x][rnk[y]];
		
		return dp[x][rnk[y]]=dp[y][rnk[x]]=self(self,fa[x],fa[y])+val[x]*val[y];
	};
	
	while(q--){
		ll x,y;
		cin>>x>>y;
		cout<<sol(sol,x,y)<<endl;
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

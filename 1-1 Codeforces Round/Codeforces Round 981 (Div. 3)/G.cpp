#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q;
	cin>>n;
	v2ct<ll> eg(n+1);
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> vis(n+1,0),dep(n+1,0),d1(n+1,0),d2(n+1,0);
	v2ct<ll> dp(n+1,vector<ll>(21,0)),fa(n+1,vector<ll>(21,0));
	
	auto DFS=[&](auto &&self,ll u)->void{
		vis[u]=1;
		for(auto v:eg[u]){
			if(!vis[v]){
				fa[v][0]=u;
				dep[v]=dep[u]+1;
				self(self,v);
				if(d1[v]+1>d1[u])
					d2[u]=d1[u],
					d1[u]=d1[v]+1;
				else if(d1[v]+1>d2[u])
					d2[u]=d1[v]+1;
			}
		}
	};
	
	dep[1]=1;
	fa[1][0]=1;
	DFS(DFS,1);
	
	for(ll i=1;i<=20;i++)
		for(ll v=1;v<=n;v++)
			fa[v][i]=fa[fa[v][i-1]][i-1];
	
	
	for(ll i=1;i<=n;i++)
		if(d1[i]+1==d1[fa[i][0]])
			dp[i][0]=d2[fa[i][0]]-dep[fa[i][0]];
		else
			dp[i][0]=d1[fa[i][0]]-dep[fa[i][0]];
	
	for(ll i=1;i<=20;i++)
		for(ll u=1;u<=n;u++)
			dp[u][i]=max(dp[u][i-1],dp[fa[u][i-1]][i-1]);
	
	cin>>q;
	
	for(ll i=1;i<=q;i++){
		ll u,k;
		cin>>u>>k;
		k=min(k,dep[u]-1);
		ll ans=d1[u],tu=u,c=0;
		while(k){
			if(k&1ll){
				ans=max(ans,dp[tu][c]+dep[u]);
				tu=fa[tu][c];
			}
			c++;
			k/=2;
		}
		cout<<ans<<' ';
	}
	cout<<endl;
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

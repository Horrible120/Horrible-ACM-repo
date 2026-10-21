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
ll vis[210002];

void solve(){
	ll n,m,tot=0;
	cin>>n>>m;
	v2ct<ll> v(n+1,vector<ll>());
	vector<ll> li(n+1),m1(n+1,-1),m2(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>li[i];
		
		
		for(ll j=1;j<=li[i];j++){
			ll x;
			cin>>x;
			v[i].emplace_back(x);
			if(x<210000)
				vis[x]=1;
		}
		
		
		
		for(ll j=0;j<=210000;j++)
			if(!vis[j]){
				if(m1[i]==-1)
					m1[i]=j;
				else{
					m2[i]=j;
					break;
				}
			}
//		OOO
		tot=max(tot,m2[i]);
		
		for(auto it:v[i]){
			if(it<210000)
				vis[it]=0;
		}
		
//		cout<<">>> "<<i<<' '<<m1[i]<<' '<<m2[i]<<endl;
	}
	
	v2ct<ll> eg(tot+2,vector<ll>());
	vector<ll> dp(tot+2,0),bk(tot+2,0);
	
	for(ll i=1;i<=n;i++)
		eg[m1[i]].emplace_back(m2[i]);
	

	
	ll mx=0;
	auto DFS=[&](auto &&self,ll u)->void{
		bk[u]=1;
		dp[u]=u;
		for(auto v:eg[u]){
			if(!bk[v]){
				self(self,v);
				dp[u]=max(dp[u],dp[v]);
			}
			else
				dp[u]=max(dp[u],dp[v]);
		}
		if(eg[u].size()>1)
			mx=max(mx,dp[u]);
	};
	
	
	
	for(ll i=1;i<=n;i++){
		if(!bk[m1[i]])
			DFS(DFS,m1[i]);
		mx=max(mx,m1[i]);
	}
	
	ll ans=0;
	for(ll i=0;i<=min(tot,m);i++){
		if(bk[i])
			ans+=max(dp[i],mx);
		else
			ans+=max(i,mx);
	}
	if(m>tot)
		ans+=(m-tot)*(tot+m+1)/2;
//	OOO
	cout<<ans<<endl;
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

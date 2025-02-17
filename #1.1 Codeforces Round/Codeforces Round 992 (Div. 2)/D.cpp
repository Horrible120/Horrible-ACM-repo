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

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n;
		cin>>n;
		vector<vector<ll>> e(n+1,vector<ll>());
		vector<ll> dep(n+1),vis(n+1),ans(n+1),fa(n+1);
		ll frt=2,bak=2*n;
		
		ll u,v;
		for(ll i=1;i<n;i++){
			cin>>u>>v;
			e[u].emplace_back(v);
			e[v].emplace_back(u);
		}
		
		std::function<void(ll, ll)> DFS=[&](ll x,ll dp){
			vis[x]=1;
			dep[x]=dp;
			if(dp&1){
				ans[x]=frt;
				frt+=2;
			}
			else{
				ans[x]=bak;
				bak-=2;
			}
			for(auto i:e[x])
				if(!vis[i]){
					fa[i]=x;
					DFS(i,dp+1);
				}
		};
		fa[1]=1;
		DFS(1,1);
		for(ll i=1;i<=n;i++)
			if(max(ans[i]-ans[fa[i]],ans[fa[i]]-ans[i])==2)
				ans[i]=ans[fa[i]]-1;
		for(ll i=1;i<=n;i++) cout<<ans[i]<<' ';
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}

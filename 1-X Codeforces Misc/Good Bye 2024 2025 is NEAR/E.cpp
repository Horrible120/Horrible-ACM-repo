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

ll tt=1;

void solve(){
	ll n,lf=0,slf=0,ans=0;
	cin>>n;
	vector<ll> e[n+1],islf(n+1),isslf(n+1);
	vector<ll> vis(n+1),sum(n+1),sz(n+1),lfs(n+1);
	
	for(ll i=1;i<n;i++){
		ll x,y;
		cin>>x>>y;
		e[x].emplace_back(y);
		e[y].emplace_back(x);
	}
	for(ll i=1;i<=n;i++){
		if(e[i].size()==1){
			lf++;
			islf[i]=1;
		}
	}
	for(ll i=1;i<=n;i++){
		for(auto it:e[i]){
			if(islf[it]&&isslf[i]==0&&islf[i]==0){
				slf++;
				isslf[i]=1;
			}
		}
	}
	
	ans+=lf*(n-lf);
	
	function<void(ll,ll)> DFS = [&](ll x,ll fa){
		vis[x]=1;
		if(isslf[x]==0&&islf[x]==0) sum[x]++;
		sz[x]++;
		vector<ll> son;
		for(auto it:e[x]){
			if(vis[it]) continue;
			DFS(it,x);
			sum[x]+=sum[it];
			son.emplace_back(it);
		}
//		OOO cout<<x<<' '<<sum[x]<<endl;
		if(islf[x]==0)
			for(auto it:son){
				if(isslf[it])
					ans+=sum[it];
			}
		if(islf[x]==0&&isslf[fa]) ans+=n-lf-slf-sum[x];
	};
	
	DFS(1,0);
	
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

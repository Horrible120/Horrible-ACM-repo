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
	ll n,sum=0,ans=0;
	cin>>n;
	vector<ll> e[n+1],a(n+1),vis(n+1),used(n+1);
	vector<vector<ll>> dp(n+1,vector<ll>(21));
	ll x,y;
	for(ll i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	for(ll i=1;i<n;i++){
		cin>>x>>y;
		e[x].emplace_back(y);
		e[y].emplace_back(x);
	}
	
	function<void(ll)> DFS=[&](ll x){
		vis[x]=1;
		ll tmp;
//		if(e[x].size()<=1ll){ dp1[x]=a[x];return;}
		
		for(ll i=1;i<=20;i++) dp[x][i]=i*a[x];
		
//		cout<<"!! 1"<<endl;
		
		for(auto it:e[x]){
			if(vis[it]) continue;
			DFS(it);
			
			for(ll i=1;i<=20;i++){
				tmp=INF;
				for(ll j=1;j<=20;j++){
					if(i==j) continue;
					tmp=min(tmp,dp[it][j]);
				}
				dp[x][i]+=tmp;
			}
		}
	};
	
	DFS(1);
	
	ll tmp=INF;
	for(ll i=1;i<=20;i++)
		tmp=min(tmp,dp[1][i]);
//	OOO
	cout<<tmp<<endl;
	
	/*function<void(ll)> DFS2=[&](ll x){
	vis[x]=1;
	if(used[x]) a[x]=0;
	
	cout<<x<<' '<<dp1[x]<<' '<<dp0[x]<<endl;
	system("pause");
	cout<<"!! 2 "<<x<<endl;
	if(e[x].size()<=1) return; 
	
	for(auto it:e[x]){
	if(vis[it]) continue;
	
	if(used[x]==0&&dp1[it]>dp0[it])
	used[it]=1;
	DFS2(it);
	}
	
	};
	
	cout<<sum<<endl;
	while(sum>0){
	vis=dp0=dp1=used=vector<ll>(n+1,0);
	DFS(1);
	ans+=sum;
	sum-=max(dp0[1],dp1[1]);
	vis=vector<ll>(n+1,0);
	if(dp0[1]<=dp1[1]) used[1]=1;
	DFS2(1);
	
	for(ll i=1;i<=n;i++) if(used[i]) cout<<i<<' ';
	cout<<endl;
	
	system("pause");
	}
	OOO
	cout<<ans<<endl;*/
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

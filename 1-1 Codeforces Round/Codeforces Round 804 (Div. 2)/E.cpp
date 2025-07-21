#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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

const ll MAXM=5e6;

void solve(){
	ll n,m;
	cin>>n>>m;
	
	vector<ll> dp(m+1,0),v(n+1,0),vis(m+1,0);
	vector<ll> cnt(m+1,0);
	
	ll r=m;
	ll ans=INF;
	ll min_val=INF;
	
	for(ll i=1;i<=m;i++){
		dp[i]=i;
	}
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(!vis[v[i]]){
			cnt[v[i]]++;
			vis[v[i]]=1;
		}
		min_val=min(min_val,v[i]);
	}
	
	for(ll l=m;l>=1;l--){
		
		for(ll j=l*l;j<=m;j+=l){
			if(vis[j]){
				cnt[dp[j]]--;
				dp[j]=min(dp[j],dp[j/l]);
				cnt[dp[j]]++;
			}else{
				dp[j]=min(dp[j],dp[j/l]);
			}
		}
		
//		OOO
//		for(ll j=1;j<=m;j++)
//			cout<<j<<' '<<dp[j]<<endl;	
		
		if(l<=min_val){
			while(r>l&&cnt[r]==0){
				r--;
			}
			ans=min(ans,r-l);
		}
	}

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

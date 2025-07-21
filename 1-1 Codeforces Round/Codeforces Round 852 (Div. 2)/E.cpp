#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n;
	vector<ll> v(n+1,0),dp(n+1,0),ans(n+1,0),prem(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
//		pref[i]=pref[i-1]+v[i];
	}
	
	sort(v.begin()+1,v.end());
	
	cin>>m;
	
//	for(ll i=1;i<=n;i++){
//		if(i-v[i]<0){
//			dp[i]=max(0ll,n-v[i]+1);
//		}else{
//			dp[i]=max(n-i+1,prem[i-v[i]]+1-v[i]);
//		}
//		prem[i]=max(prem[i-1],dp[i]);
//		cout<<i<<' '<<dp[i]<<endl;
//	}
	
	for(ll i=1;i<=n;i++){
		if(i-v[i]<0){
			dp[i]=i-v[i]+1;
		}else{
			dp[i]=max(1ll,prem[i-v[i]]+1);
		}
		prem[i]=max(prem[i-1],dp[i]);
//		cout<<i<<' '<<dp[i]<<endl;
	}
	
//	cout<<endl;
	
	for(ll i=1;i<=n;i++){
		dp[i]+=n-i;
//		cout<<i<<' '<<dp[i]<<endl;
	}
	
//	cout<<endl;
	
	ll pos=1;
	for(ll i=n;i>=1;i--){
		while(pos<=dp[i]){
			ans[pos++]=i;
		}
	}
	
//	for(ll i=0;i<=n;i++)
//		cout<<i<<' '<<ans[i]<<endl;
//	cout<<endl;
	
	for(ll i=1;i<=m;i++){
		ll x;
		cin>>x;
		cout<<ans[x]<<'\n';
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

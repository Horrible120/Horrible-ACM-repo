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
	ll n,m,ans=0;
	cin>>n>>m;
	vector<vector<ll>> dp(n+2,vector<ll>(n+2,0));
	
	dp[0][0]=1;
	
	for(ll i=0;i<n;i++){
		for(ll j=0;j<=i;j++){
			dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j])%m;
			dp[i+1][j]=(dp[i+1][j]+dp[i][j]*(n-i)*(j+1))%m;
		}
	}
	
	for(ll i=0;i<=n;i++)
//		cout<<i<<' '<<dp[n][i]<<endl;
		ans=(ans+dp[n][i])%m;
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

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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,a,x,y,m,k,ans=0;
	cin>>n>>a>>x>>y>>m>>k;
	vector<ll> v(n+1,0),pre(n+1,0);
	vector<vector<ll>> dp(k+1,vector<ll>(n+1,0));
	
	v[1]=a%Mod;
	for(ll i=2;i<=n;i++){
		v[i]=(v[i-1]*x+y)%m;
	}
	
	dp[0][0]=v[1];
	for(ll i=1;i<n;i++){
		dp[0][i]=(dp[0][i-1]+v[i+1])%Mod;
	}
	
	for(ll i=1;i<=k;i++){
		for(ll j=1;j<=n;j++){
			dp[i][j]=(dp[i-1][j-1]+dp[i][j-1])%Mod;
		}
	}
	
	for(ll i=1;i<=n;i++){
		ans^=i*dp[k][i];
	}
//	5 8 2 3 100 1
//	OOO
	cout<<ans<<endl;
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

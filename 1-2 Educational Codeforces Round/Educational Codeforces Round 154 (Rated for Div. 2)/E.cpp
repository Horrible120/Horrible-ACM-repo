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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	
	vector<vector<ll>> dp(n+1,vector<ll>(k+1,0));
	
	dp[0][0]=1;
	
	for(ll i=1;i<=n;i++){
		ll sum=0;
		for(ll j=k-1;j>=1;j--){
			sum+=dp[i-1][j];
			dp[i][j]=(dp[i-1][j-1]*(k-j+1)+sum)%Mod;
		}
		dp[i][0]=dp[i-1][k-1];
	}
	
	ll ans=0,cnt=1;
	for(ll i=n;i>=1;i--){
		ans=(ans+cnt*dp[i][0])%Mod;
		cnt=cnt*k%Mod;
	}
	cout<<ans<<endl;
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

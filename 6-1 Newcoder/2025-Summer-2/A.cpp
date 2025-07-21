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
	ll n,ans=0;
	cin>>n;
	vector<ll> v(n+1,0);
	vector<array<ll,2>> dp(n+1);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	if(v[1]==-1){
		dp[1][1]=dp[1][0]=1;
	}else{
		dp[1][v[1]]=1;
	}
	
	
	for(ll i=2;i<=n;i++){
		if(v[i]==0){
			dp[i][1]=0;
			dp[i][0]=(dp[i-1][1]+dp[i-1][0])%Mod;
			ans=(ans+dp[i-1][1])%Mod;
		}else if(v[i]==1){
			dp[i][0]=0;
			dp[i][1]=(dp[i-1][1]+dp[i-1][0])%Mod;
		}else{
			dp[i][1]=(dp[i-1][1]+dp[i-1][0])%Mod;
			dp[i][0]=(dp[i-1][1]+dp[i-1][0])%Mod;
			ans=(ans*2+dp[i-1][1])%Mod;
		}
//		cout<<i<<' '<<dp[i][0]<<' '<<dp[i][1]<<' '<<ans<<endl;
	}
//	cout<<endl;
//	OOO
	cout<<(ans+dp[n][1])%Mod<<endl;
	
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

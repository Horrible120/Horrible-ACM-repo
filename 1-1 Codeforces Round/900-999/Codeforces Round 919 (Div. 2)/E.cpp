#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k,ans=0;
	cin>>n>>k;
	v2ct<ll> dp(n+1,vector<ll>(n+1,0));
	for(ll i=1;i<=n;i++)
		dp[0][i]=1;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=i;j++){
			for(ll l=1;l+j<=k+1&&j*l<=i;l++)
				dp[i][j]=(dp[i][j]+dp[i-j*l][l])%Mod;
		}
	}
	for(ll i=1;i<=n;i++)
		ans+=dp[n][i];
//	OOO
	cout<<ans%Mod<<endl;
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

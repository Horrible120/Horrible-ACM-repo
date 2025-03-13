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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,ans=0;
	cin>>n;
	
	vector<ll> v(2*n+1);
	v2ct<ll> dp(2*n+1,vector<ll>(2*n+1,0));
	for(ll i=1;i<=n;i++)
		cin>>v[i],v[n+i]=v[i];
	
	for(ll i=2;i<=n-1;i++)
		for(ll j=1;j+i<=2*n;j++){
			ll l=j,r=j+i;
			for(ll k=l;k<=r-1;k++)
				dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
			for(ll k=l+1;k<=r-1;k++)
				dp[l][r]=max(dp[l][r],dp[l+1][k-1]+dp[k+1][r-1]+v[l]*v[r]*v[k]);
		}
	for(ll i=1;i<=n;i++)
		ans=max(ans,dp[i][i+n-1]);
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

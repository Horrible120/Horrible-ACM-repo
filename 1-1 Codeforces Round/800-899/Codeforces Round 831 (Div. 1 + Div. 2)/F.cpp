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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),cnt(n+1,0);
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		cnt[x]++;
		v[cnt[x]]++;
	}
	
	for(ll i=1;i<=n;i++){
		v[i]+=v[i-1];
//		cout<<v[i]<<' ';
	}
	
//	cout<<endl;
	
	vector<vector<ll>> dp(n+1,vector<ll>(n+1,0)),pre(n+1,vector<ll>(n+1,0));
	
//	for(ll i=0;i<=n;i++){
//		dp[0][i]=1;
//	}
	
	vector<ll> sum(n+1,0);
	
	for(ll j=0;j<=v[1];j++){
		dp[j][j]=1;
		sum[j]=1;
	}
	
	for(ll i=2;i<=n;i++){
		for(ll j=v[i];j>=0;j--){
			pre[j][0]=dp[j][0];
			for(ll k=1;k*(i-1)<=n;k++){
				pre[j][k]=(dp[j][k]+pre[j][k-1])%Mod;
			}
		}
		
//		for(ll j=0;j<=n;j++)
//			for(ll k=0;k<=n;k++)
//				cout<<dp[j][k]<<" \n"[k==n];
//		cout<<endl;
		
		for(ll j=v[i];j>=0;j--){
			dp[j][0]=sum[j];
			for(ll k=1;k<=j&&k*i<=n;k++){
				dp[j][k]=(sum[j-k]-pre[j-k][k-1]+Mod)%Mod;
				sum[j]=(sum[j]+dp[j][k])%Mod;
			}
		}
		
//		for(ll j=0;j<=n;j++)
//			for(ll k=0;k<=n;k++)
//				cout<<dp[j][k]<<" \n"[k==n];
//		cout<<endl;
	}
	
//	ll ans=0;
//	for(ll i=0;i<=n;i++){
//		ans=(ans+dp[n][i])%Mod;
//	}
	
//	OOO
	cout<<(dp[n][0]+dp[n][1])%Mod<<endl;
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

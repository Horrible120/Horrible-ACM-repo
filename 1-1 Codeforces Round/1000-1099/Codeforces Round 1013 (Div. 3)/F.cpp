#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m,d,ans=0;
	cin>>n>>m>>d;
	v2ct<ll> v(n+1,vector<ll>(m+1,0)),dp(n+1,vector<ll>(m+1,0)),pdp(n+1,vector<ll>(m+1,0));
	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		for(ll j=1;j<=m;j++)
			v[i][j]=(s[j-1]=='X'?1:0);
	}
	
	for(ll i=1;i<=m;i++){
		if(v[1][i]==1)
			dp[1][i]=1;
		pdp[1][i]=pdp[1][i-1]+dp[1][i];
	}
	
	for(ll i=1;i<=m;i++)if(v[1][i])
		dp[1][i]=pdp[1][min(i+d,m)]-pdp[1][max(0ll,i-d-1)];
	
	
	for(ll k=2;k<=n;k++){
		for(ll i=1;i<=m;i++)
			pdp[k-1][i]=pdp[k-1][i-1]+dp[k-1][i];
		
		for(ll i=1;i<=m;i++)if(v[k][i])
			dp[k][i]=(pdp[k-1][min(i+d-1,m)]-pdp[k-1][max(0ll,i-d)]+Mod)%Mod;
		
		for(ll i=1;i<=m;i++)
			pdp[k][i]=pdp[k][i-1]+dp[k][i];
		
		for(ll i=1;i<=m;i++)if(v[k][i])
			dp[k][i]=(pdp[k][min(i+d,m)]-pdp[k][max(0ll,i-d-1)]+Mod)%Mod;
	}
	
	for(ll i=1;i<=m;i++)if(v[n][i])ans+=dp[n][i];
	
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

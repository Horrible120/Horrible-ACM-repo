#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 998244353;

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	ll k,n;
	cin>>k>>n;
	v2ct<ll> dp(20,vector<ll>(k+3,0));
	vector<ll> ans(k+1),c(k+3);
	
	c[0]=1;
	for(ll i=1;i<=k+2;i++)
		c[i]=((c[i-1]*(n-i+2)%Mod)*inv(i))%Mod;
	
	dp[0][1]=1;
	for(ll i=1;i<=k;i++)
		for(ll j=2*i;j<=k;j+=i)
			for(ll x=0;x<=17;x++)
				dp[x+1][j]=(dp[x+1][j]+dp[x][i])%Mod;
	
	for(ll i=1;i<=k;i++)
		for(ll j=0;j<=17;j++)
			if(n>=j)
				ans[i]=(ans[i]+dp[j][i]*c[j+1])%Mod;
	ans[1]=n;
	for(ll i=1;i<=k;i++)
		cout<<ans[i]<<' ';
	cout<<endl;
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

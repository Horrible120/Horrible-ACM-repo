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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	ll n,l,k;
	cin>>n>>l>>k;
	v2ct<ll> dp(l+2,vector<ll>(n+1));
	vector<ll> ans(n+1);
	
	dp[l+1][n]=1;
	for(ll i=l;i>=1;i--){
		ll tmp=inv(i);
		for(ll p=1;p<=n;p++)
			for(ll q=1;q<=n;q++){
				ll bg=(q-p+n-1)%n+1;
				ll cnt=(double)(i-bg)/n+1;
//				cout<<i<<' '<<p<<' '<<q<<' '<<bg<<' '<<cnt<<' '<<endl;
				dp[i][q]=(dp[i][q]+dp[i+1][p]*tmp%Mod*cnt)%Mod;
			}
	}
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=l;j++)
			ans[i]+=dp[j][i];
	
	for(ll i=1;i<=n;i++)
		cout<<ans[i]%Mod<<' ';
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

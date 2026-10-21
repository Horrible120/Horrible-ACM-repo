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

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd((a+Mod)%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void init(){
	
	
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),dp(n+1,0),p(101,0);
	vector<vector<ll>> g(101,vector<ll>(n+1,0));
	
	for(ll i=0;i<=99;i++){
		p[i]=inv(100)*i%Mod;
	}
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	ll ans=0;
	
//	OOO
	
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<=99;j++){
			g[j][i]=(g[j][i-1]*p[j]+dp[i-1]*p[j]%Mod*p[j])%Mod;
		}
		dp[i]=((g[v[i]][i]+1LL)*inv(1-p[v[i]])%Mod+Mod)%Mod;
		ans=(ans+dp[i])%Mod;
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

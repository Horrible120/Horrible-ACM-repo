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

const ll N=(1<<20)+1;
ll fact[N],iv[N],p2[N];

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void init(){
	fact[0]=1;
	p2[0]=1;
	
	for(ll i=1;i<N;i++){
		p2[i]=p2[i-1]*2%Mod;;
		fact[i]=fact[i-1]*i%Mod;
	}
	
	iv[N-1]=inv(fact[N-1]);
	
	for(ll i=N-2;i>=0;i--){
		iv[i]=iv[i+1]*(i+1)%Mod;
	}
}

ll C(ll n,ll m){
	if(n<m) return 0;
	return fact[n]*iv[m]%Mod*iv[n-m]%Mod;
}

void solve(){
	ll n;
	cin>>n;
	vector dp(n+1,vector<ll>((1<<n)+1,0));
	
	dp[1][1]=1;
	
	for(ll i=2;i<=n;i++){
		ll sum=0,siz=(1<<n-i+1);
		for(ll j=1;j<=(1<<n);j++){
			dp[i][j]=sum;
			sum=(sum+dp[i-1][j]*C((1<<n)-j-siz,siz-1)%Mod*fact[siz]*2ll)%Mod;
		}
	}
	
	ll sum=0;
	for(ll i=1;i<=(1<<n);i++){
		cout<<sum<<'\n';
		sum=(sum+dp[n][i]*2)%Mod;
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
//	cout<<iv[1]<<endl;
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}


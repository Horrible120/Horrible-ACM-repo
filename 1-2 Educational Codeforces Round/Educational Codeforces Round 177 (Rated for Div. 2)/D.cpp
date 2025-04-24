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
ll fct[500001],iv[500001];

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
	ll n=500000;
	fct[0]=1;
	iv[0]=1;
	for(ll i=1;i<=n;i++)
		fct[i]=i*fct[i-1]%Mod,iv[i]=inv(fct[i]);
}

ll C(ll n,ll m){
	if(n<m) return 0;
	
	return fct[n]*iv[m]%Mod*iv[n-m]%Mod;
}

void solve(){
	vector<ll> cnt(30,0),pv(30,0);
	ll sum=0,ans=0;
	
	for(ll i=1;i<=26;i++)
		cin>>cnt[i],sum+=cnt[i],pv[i]=cnt[i]+pv[i-1];
	
	v2ct<ll> dp(30,vector<ll>(sum+4,0));
	
	dp[0][0]=1;
//	cout<<sum<<endl;
	
	for(ll i=1;i<=26;i++){
//		
		if(cnt[i]==0)
			for(ll j=0;j<=sum;j++)
				dp[i][j]=dp[i-1][j];
		else{
			for(ll j=0;j+cnt[i]<=(sum+1)/2;j++)
				dp[i][j+cnt[i]]=(dp[i][j+cnt[i]]+dp[i-1][j]*C((sum+1)/2-j,cnt[i]))%Mod;
			for(ll j=0;j<=sum/2+1;j++)
				dp[i][j]=(dp[i][j]+dp[i-1][j]*C(sum/2-(pv[i]-j)+cnt[i],cnt[i]))%Mod;
		}
	}
	cout<<dp[26][(sum+1)/2]<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

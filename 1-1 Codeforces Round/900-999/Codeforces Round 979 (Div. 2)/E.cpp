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
ll fct[200001],iv[200001];

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
	ll n=2e5;
	fct[0]=1;
	for(ll i=1;i<=n;i++)
		fct[i]=fct[i-1]*i%Mod;
	
	iv[n]=inv(fct[n]);
	for(ll i=n-1;i>=0;i--)
		iv[i]=iv[i+1]*(i+1)%Mod;
//	cout<<iv[0]<<endl;
}

ll ccb(ll n,ll m){
	if(m<0||n<0||n<m)
		return 0;
	return (fct[n]*iv[m]%Mod*iv[n-m]%Mod);
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+2,0),cnt(n+2,0),min_val(n+2,0),sufp(n+2,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i],
		cnt[v[i]]++;
	
	min_val[0]=cnt[0];
	for(ll i=1;i<=n;i++)
		min_val[i]=min(cnt[i],min_val[i-1]);
	
	sufp[n]=1;
	for(ll i=n-1;i>=0;i--){
		sufp[i]=sufp[i+1];
		for(ll j=1;j<=cnt[i];j++)
			sufp[i]=sufp[i]*2%Mod;
	}
	
	ll ans=0;
	vector<ll> cntf,pref(n+2,1);
	
	for(ll i=0;i<=n;i++){
		cntf.assign(cnt[i]+2,0);
		
		for(ll j=cnt[i];j>=0;j--)
			cntf[j]=(cntf[j+1]+ccb(cnt[i],j))%Mod;
		
		for(ll j=0;j<=min_val[i];j++){
			ans=(ans+j*sufp[i+1]%Mod*(pref[j]*ccb(cnt[i],j)%Mod+(pref[j]-pref[j+1]+Mod)*cntf[j+1]%Mod))%Mod;
		}
		
		for(ll j=min_val[i]+1;j>=0;j--)
			pref[j]=pref[j]*cntf[j]%Mod;
	}
	
//	OOO
	cout<<ans<<endl;
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

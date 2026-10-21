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
ll fact[200001],iv[200001];

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
	fact[0]=1;
	for(ll i=1;i<=n;i++)
		fact[i]=fact[i-1]*i%Mod;
	iv[n]=inv(fact[n]);
	for(ll i=n-1;i>=0;i--)
		iv[i]=iv[i+1]*(i+1)%Mod;
}

ll cb(ll n,ll m){
	if(n<m||m<0) return 1ll;
	return fact[n]*iv[m]%Mod*iv[n-m]%Mod;
}

void solve(){
	ll n,n1,n2,ans=1;
	cin>>n>>n1>>n2;
	vector<ll> pref,suff;
	pref.emplace_back(1);
	for(ll i=1;i<=n1;i++){
		ll x;
		cin>>x;
		pref.emplace_back(x);
	}
	for(ll i=1;i<=n2;i++){
		ll x;
		cin>>x;
		suff.emplace_back(x);
	}
	suff.emplace_back(n);
	
	for(ll i=1;i<=n1;i++){
		ll tmp=pref[i]-2;
		ll cnt=tmp>0?fact[pref[i]-pref[i-1]-1]*cb(tmp,pref[i]-pref[i-1]-1)%Mod:1ll;
		ans=ans*cnt%Mod;
	}
	
	for(ll i=n2-1;i>=0;i--){
		ll tmp=n-suff[i]-1;
		ll cnt=tmp>0?fact[suff[i+1]-suff[i]-1]*cb(tmp,suff[i+1]-suff[i]-1)%Mod:1ll;
		ans=ans*cnt%Mod;
	}
	
//	OOO
	if(pref[n1]!=suff[0]||pref[1]!=1||suff[n2-1]!=n){
		cout<<0<<endl;
	}
	else{
		cout<<ans*cb(n-1,pref[n1]-1)%Mod<<endl;
	}
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

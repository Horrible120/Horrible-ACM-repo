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

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

vector<ll> fact(300001,0),ifact(300001,0),H(150000,0);

void init(){
	fact[0]=1;
	ll n=300000;
	for(ll i=1;i<=n;i++){
		fact[i]=fact[i-1]*i%Mod;
	}
	ifact[n]=inv(fact[n]);
	for(ll i=n-1;i>=0;i--){
		ifact[i]=ifact[i+1]*(i+1)%Mod;
	}
	H[0]=1;
	for(ll i=1;i<=n/2;i++){
		H[i]=fact[2*i]*ifact[i]%Mod*ifact[i]%Mod*inv(i+1)%Mod;
	}
}

void solve(){
	ll n,k,flag=1,ans=1;
	
	cin>>n>>k;
	
	vector<ll> v(n+2,0);
	for(ll i=1;i<=k;i++){
		ll l,r;
		cin>>l>>r;
		ll tmp=rnd();
		v[l]^=tmp;
		v[r+1]^=tmp;
	}
	
	map<ll,ll> cnt;
	
	for(ll i=1;i<=n;i++){
		v[i]^=v[i-1];
		cnt[v[i]]++;
	}
	
	for(auto [x,ct]:cnt){
		if(ct%2==1) flag=0;
		ans=ans*H[ct/2]%Mod;
	}
	
	if(flag){
		cout<<ans<<endl;
	}else{
		cout<<0<<endl;
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

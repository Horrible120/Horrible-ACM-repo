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

vector<ll> fact(400001,0),ifact(400001,0);

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
	ll n=400000;
	fact[0]=1;
	for(ll i=1;i<=n;i++){
		fact[i]=fact[i-1]*i%Mod;
	}
	ifact[n]=inv(fact[n]);
	for(ll i=n-1;i>=0;i--){
		ifact[i]=ifact[i+1]*(i+1)%Mod;
	}
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),pre(n+1,0),ppre(n+1,0),vsum(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		v[i]%=Mod;
		pre[i]=(pre[i-1]+v[i])%Mod;
		ppre[i]=(ppre[i-1]+pre[i])%Mod;
	}
	
	for(ll i=1;i<=n;i++){
		vsum[i]=((ppre[n]-ppre[i-1]-ppre[n-i])%Mod+Mod)%Mod;
//		cout<<i<<' '<<vsum[i]<<endl;
	}
	
	ll ans=0;
	
	ans=(ans+n*vsum[1])%Mod;
	
	for(ll i=2;i<=n;i++){
		for(ll x=1;x<=2;x++){
			for(ll y=1;y<=2;y++){
				ll res=n-x-y-i+2;
				if(res<0||res%2==1) continue;
				
				ll tmp=fact[i-1ll+res/2ll]*ifact[res/2ll]%Mod*ifact[i-1ll]%Mod;
				
				(ans+=tmp*((res)*inv(i)%Mod+1ll)%Mod*vsum[i]%Mod)%=Mod;
				
				if(x==2) (ans+=tmp*pre[n-i+1ll]%Mod)%=Mod;
				
				if(y==2) (ans+=tmp*((pre[n]-pre[i-1ll]+Mod)%Mod))%=Mod;
				
			}
		}
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

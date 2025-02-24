#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;
ll c[5000];
ll ic[5001];

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

ll cp(ll n,ll m){
	return c[n]*ic[m]%Mod*ic[n-m]%Mod;
}

void solve(){
	ll n;
	cin>>n;
	ll ans=2*n+1;
	for(ll i=1;i<=n;i++){//	选取了 n-i 个，相当于没选 i 个
		//	此时要求取第 p=n-i+1 个没选的数；
		ll p=min(n-i+1,i);
		for(ll x=p;x<=n+p-i;x++){//	选到了 x 的组合数
			ll tmp=cp(x-1,p-1)*cp(n-x,i-p)%Mod;
			ll pls= p==n-i+1?x:(n-i+n-i+1);
			ans=(ans+tmp*pls)%Mod;
		}
	}
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	cin >> tt;	//非多组测试数据时注释掉即可
	
	c[0]=1;
	ic[0]=1;
	for(ll i=1;i<=5000;i++){
		c[i]=c[i-1]*i%Mod;
		ic[i]=inv(c[i]);
	}
		
	
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

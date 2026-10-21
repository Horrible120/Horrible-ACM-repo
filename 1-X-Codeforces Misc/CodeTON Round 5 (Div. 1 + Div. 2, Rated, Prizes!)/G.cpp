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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)
			ans=ans*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return ans;
}

void solve(){
	ll n,m,v;
	cin>>n>>m>>v;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++)
		cin>>a[i];

	ll lim=min(n,m),inv=qpow(n,Mod-2);
	vector<ll> f(lim+1),g(lim+1);
	f[0]=1;

	for(ll i=1;i<=n;i++){
		fill(g.begin(),g.end(),0);
		ll val=v*i%Mod*inv%Mod;
		for(ll j=0;j<=min(i-1,m);j++){
			g[j]=(g[j]+f[j]*((a[i]+j*v)%Mod))%Mod;
			if(j<m)
				g[j+1]=(g[j+1]+f[j]*(m-j)%Mod*val)%Mod;
		}
		f.swap(g);
	}

	ll ans=0;
	for(ll j=0;j<=lim;j++)
		ans=(ans+f[j])%Mod;
	cout<<ans<<'\n';
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

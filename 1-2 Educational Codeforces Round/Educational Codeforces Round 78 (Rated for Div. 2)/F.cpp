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

ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)
			res=res*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return res;
}

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;

	ll lim=min(n,k);
	vector<ll> f(lim+1),g(lim+1);
	f[0]=1;

	for(ll i=0;i<k;i++){
		for(ll j=0;j<=lim;j++)
			g[j]=0;

		for(ll j=0;j<=min(i,lim);j++){
			g[j]=(g[j]+f[j]*j)%Mod;
			if(j<lim)
				g[j+1]=(g[j+1]+f[j]*(n-j))%Mod;
		}
		f.swap(g);
	}

	ll inv=qpow(m,Mod-2),pw=1,ans=0;
	for(ll j=1;j<=lim;j++){
		pw=pw*inv%Mod;
		ans=(ans+f[j]*pw)%Mod;
	}
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

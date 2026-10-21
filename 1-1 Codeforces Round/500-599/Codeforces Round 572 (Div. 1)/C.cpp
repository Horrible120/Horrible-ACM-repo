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

void solve(){
	ll n,k;
	cin>>n>>k;

	vector<ll> a(n+1),p(n+1),f(n+1),g(n+1);
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	sort(a.begin()+1,a.end());

	ll m=(a[n]-a[1])/(k-1),ans=0;
	for(ll d=1;d<=m;d++){
		ll r=0;
		for(ll i=1;i<=n;i++){
			while(r+1<i&&a[i]-a[r+1]>=d)
				r++;
			p[i]=r;
		}

		for(ll i=0;i<=n;i++)
			f[i]=i;

		for(ll j=2;j<=k;j++){
			g[0]=0;
			for(ll i=1;i<=n;i++)
				g[i]=(g[i-1]+f[p[i]])%Mod;

			f.swap(g);
		}

		ans=(ans+f[n])%Mod;
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

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

void solve(){
	ll n,q,m=1<<20,sum=0;
	cin>>n>>q;

	vector<ll> a(n+1),cnt(m);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
		sum+=a[i];
	}

	for(ll i=0;i<20;i++)
		for(ll j=0;j<m;j++)
			if(!(j>>i&1)) cnt[j]+=cnt[j|(1ll<<i)];

	vector<vector<ll>> f(20);
	for(ll i=0;i<20;i++){
		ll lim=1ll<<(19-i),w=1ll<<i;
		f[i].resize(lim);
		for(ll j=1;j<=n;j++)
			if(!(a[j]&w)) f[i][a[j]>>(i+1)]+=a[j]&(w-1);
		for(ll j=0;j<19-i;j++)
			for(ll s=0;s<lim;s++)
				if(!(s>>j&1)) f[i][s]+=f[i][s|(1ll<<j)];
	}

	while(q--){
		ll k;
		cin>>k;
		if(k>=n*m-sum){
			cout<<(sum+k)/n<<'\n';
			continue;
		}
		ll ans=0;
		for(ll i=19;i>=0;i--){
			ll w=1ll<<i,cost=(n-cnt[ans|w])*w-f[i][ans>>(i+1)];
			if(cost<=k){
				k-=cost;
				ans|=w;
			}
		}
		cout<<ans<<'\n';
	}
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

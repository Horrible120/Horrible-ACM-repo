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
	ll n;
	cin >> n;
	vector<ll> a(n+1);
	for ( ll i=1; i<=n; i++ )
		cin >> a[i];

	vector<ll> fa(n+1), val(n+1), pos(n+1,-1), nxt(n+2), dp(n+2);
	map<pair<ll,ll>,ll> to;
	ll cur=0, tot=0;
	pos[0]=0;

	for ( ll i=1; i<=n; i++ ) {
		if ( cur && val[cur]==a[i] )
			cur=fa[cur];
		else {
			ll &id=to[{cur,a[i]}];
			if ( !id ) {
				id=++tot;
				fa[id]=cur;
				val[id]=a[i];
			}
			cur=id;
		}

		if ( pos[cur]!=-1 )
			nxt[pos[cur]+1]=i;
		pos[cur]=i;
	}

	ll ans=0;
	for ( ll i=n; i>=1; i-- ) {
		if ( nxt[i] )
			dp[i]=1+dp[nxt[i]+1];
		ans+=dp[i];
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}

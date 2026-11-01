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
	ll n,m;
	cin >> n >> m;
	vector<ll> pre(m+1),f(m+1);
	for (ll i=1;i<=n;i++) {
		ll pos;
		cin >> pos;
		pre[pos]^=1;
	}
	for (ll i=1;i<=m;i++)
		pre[i]^=pre[i-1];

	ll q;
	cin >> q;
	vector<pair<ll,ll>> ask(q);
	for (auto &[l,r]:ask)
		cin >> l >> r;
	string ans(q,'B');

	for (ll len=1;len<m;len*=2) {
		for (ll i=m;i>=1;i--) {
			f[i]=pre[min(m,i+len-1)]^pre[i-1];
			if (i+2*len<=m)
				f[i]^=f[i+2*len];
		}

		for (ll i=0;i<q;i++) {
			auto [l,r]=ask[i];
			ll st=l+len;
			if (st>r)
				continue;
			ll pos=st+(r-st)/(2*len)*(2*len);
			ll val=f[st]^f[pos]^pre[min(r,pos+len-1)]^pre[pos-1];
			if (val)
				ans[i]='A';
		}
	}

	cout << ans << '\n';
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

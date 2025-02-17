#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt = 1;

void solve() {
	ll n, ans = 0, cnt0 = 0;
	cin >> n;
	vector<ll> v(n + 1), rv(1);
	for (ll i = 1; i <= n; i++) {
		cin >> v[i];
		if (v[i] > 0 || cnt0 == 0)
			rv.emplace_back(v[i]);
		if (v[i] == 0) cnt0++;
	}
	ans = n - cnt0;
	ll mx = 0;
	map<ll, ll> mp;
	vector<ll> prm(n + 1, INF);
	for (ll i = 1; i < ll( rv.size()); i++)
		prm[i] = min(prm[i - 1], rv[i]);
	for (ll i = rv.size() - 1; i >= 1; i--) {
		mp[rv[i]] = 1;
		while (mp[mx]) mx++;
		if (mx > prm[i - 1]) break;
		if (i == 1) ans = max(ans, ll(rv.size() - 1));
	}

//	OOO
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
	}

	cout.flush();
	return 0;
}

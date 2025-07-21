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
using pll = pair<ll, ll>;
template <typename T> using v2ct = vector<vector<T >>;
template <typename T> using v3ct = vector<vector<vector<T >>>;

template <typename T, typename Compare = std::less<T >>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF) + time(0) );

ll tt = 1;

void solve() {
	ll n, m, ans = 0;
	cin >> n >> m;
	vector<vector<ll>> mp(n + 2, vector<ll>(m + 2, 0));

	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= m; j++) {
			cin >> mp[i][j];
		}
	}

	vector<array<ll, 3 >> node;

	node.emplace_back(array<ll, 3>({mp[1][1], 1, 1}));

	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= m; j++) {
			if(i>1 || j > 1) {
				if (mp[i][j] > mp[i - 1][j] && mp[i][j] > mp[i][j - 1] && mp[i][j] > mp[i + 1][j] && mp[i][j] > mp[i][j + 1]) {
					node.emplace_back(array<ll, 3>({mp[i][j], j, i}));
					ans += 1ll << 34;
				}
			}
		}
	}

	sort(node.begin(), node.end());

	if (node.size() > 1) {
		for (ll i = 1; i < node.size(); i++) {
			ans += 114 * abs(node[i][2] - node[i - 1][2]) + 5141 * abs(node[i][1] - node[i - 1][1]) + 919810 * abs(node[i][0] - node[i - 1][0]);
		}
	}
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

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
	vector<vector<ll>> val(n+2,vector<ll>(m+2)),dif=val;
	for (ll i=1;i<=n;i++) {
		string s;
		cin >> s;
		for (ll j=1;j<=m;j++)
			val[i][j]=(s[j-1]=='B');
	}

	ll ans=0;
	for (ll i=1;i<=n;i++)
		for (ll j=1;j<=m;j++) {
			dif[i][j]=val[i][j]^val[i+1][j]^val[i][j+1]^val[i+1][j+1];
			ans+=dif[i][j];
		}

	for (ll i=1;i<n;i++)
		for (ll j=1;j<m;j++)
			if (dif[i][j] && dif[i][m] && dif[n][j] && dif[n][m]) {
				cout << ans-1 << '\n';
				return;
			}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}

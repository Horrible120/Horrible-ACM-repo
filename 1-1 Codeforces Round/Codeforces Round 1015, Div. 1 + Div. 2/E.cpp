#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll, ll>;
template <typename T> using v2ct = vector<vector<T >>;
template <typename T> using v3ct = vector<vector<vector<T >>>;

template <typename T, typename Compare = std::less<T >>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF) + time(0) );

ll tt = 1;
ll fact[5001], iv[5001];

void exgcd(ll a, ll b, ll& d, ll& x, ll& y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		exgcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}
ll inv(ll a) {
	ll d, x, y;
	exgcd(a % Mod, Mod, d, x, y);
	return d == 1 ? (x + Mod) % Mod : -1;
}

void init() {
	ll n = 5000;
	fact[0] = 1;
	iv[0] = 1;
	for (ll i = 1; i <= n; i++) {
		fact[i] = fact[i - 1] * i % Mod;
		iv[i] = inv(fact[i]) % Mod;
	}
}

ll cb(ll i, ll j) {
	if (i >= j)
		return fact[i] * iv[j] % Mod * iv[i - j] % Mod;
	return 0;
}

void solve() {
	ll n, ans = 0;
	cin >> n;

	vector<ll> v(n + 1, 0), need(n + 1, 1), in;
	v2ct<ll> emp(n + 2, vector<ll>(n + 2, 0));
	for (ll i = 1; i <= n; i++) {
		cin >> v[i];
		if (v[i] >= 0)
			in.emplace_back(v[i]), need[v[i]] = 0;
	}

	for (ll i = 1; i <= n; i++)
		need[i] += need[i - 1];	//凑齐包括 i 在内的之前的数，需要几个空位

	sort(in.begin(), in.end());
	ll incnt = in.size();
	vector<ll> vis(n + 1, 0);	//那些数出现过
	for (ll i = 1; i <= n; i++) {
		for (ll j = 0; j <= n; j++)
			vis[j] = 0;
		ll cnt = 0, mcnt = 0;	//前cnt个存在于原数组中的数全都出现了，有几个空位（-1）
		for (ll j = i; j <= n; j++) {
			if (v[j] >= 0)
				vis[v[j]] = 1;
			else
				mcnt++;
			while (cnt < incnt && vis[in[cnt]])	//更新cnt
				cnt++;
			if (cnt == incnt)
				emp[mcnt][n]++;
			else
				emp[mcnt][in[cnt]]++;	//具有 mcnt 个-1，并且有着in[cnt]之前的全部存在的数
		}
	}

	for (ll i = 0; i <= n; i++)
		for (ll j = n; j >= 0; j--)
			emp[i][j] += emp[i][j + 1];	//具有 mcnt 个-1，并且有着 j 之前的全部存在的数的区间数（后缀和统计）

	for (ll i = 1; i <= n; i++)	//mex
		for (ll j = 0; j <= n; j++)
			if (j >= need[i - 1])
				ans = (ans + emp[j][i] * cb(j, need[i - 1]) % Mod * fact[need[i - 1]] % Mod * fact[need[n - 1] - need[i - 1]]) % Mod;
//	OOO
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
	}

	cout.flush();
	return 0;
}

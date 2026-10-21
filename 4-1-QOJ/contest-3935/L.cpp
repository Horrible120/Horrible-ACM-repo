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

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

ll floor_div(ll a, ll b) {
	assert(b > 0);
	if (a >= 0) {
		return a / b;
	} else {
		return (a - b + 1) / b;
	}
}

ll ceil_div(ll a, ll b) {
	return floor_div(a + b - 1, b);
}

void solve(){
	ll a, b, c, d, e, l, r;
	cin >> a >> b >> c >> d >> e >> l >> r;
	
	ll ans = 0;
	for (ll x3 = l; x3 <= r; ++x3) {
		for (ll x4 = l; x4 <= r; ++x4) {
			ll v = e - c * x3 - d * x4;
			if (a == 0 && b == 0) {
				if (v == 0) {
					ans += (r - l + 1) * (r - l + 1);
				}
				continue;
			} else if (a == 0) {
				if (v % b == 0 && v / b >= l && v / b <= r) {
					ans += r - l + 1;
				}
				continue;
			} else if (b == 0) {
				if (v % a == 0 && v / a >= l && v / a <= r) {
					ans += r - l + 1;
				}
				continue;
			}
			ll g = std::gcd(a, b);
			if (v % g == 0) {
				ll g1, x1, x2;
				exgcd(a, b, g1, x1, x2);
				ll lo1 = 1, hi1 = 0;
				if (b > 0) {
				    lo1 = ceil_div(g * l - v * x1, b);
				    hi1 = floor_div(g * r - v * x1, b);
				} else {
					lo1 = ceil_div(-g * r + v * x1, -b);
					hi1 = floor_div(-g * l + v * x1, -b);
				}
				ll lo2 = 1, hi2 = 0;
				if (a > 0) {
				    lo2 = ceil_div(v * x2 - g * r, a);
				    hi2 = floor_div(v * x2 - g * l, a);
				} else {
					lo2 = ceil_div(-v * x2 + g * l, -a);
					hi2 = floor_div(-v * x2 + g * r, -a);
				}
				ll lo = std::max(lo1, lo2);
				ll hi = std::min(hi1, hi2);
				if (lo <= hi) {
			   	    ans += hi - lo + 1;
				}
			}
		}
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	// cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	long double n, r, h, x0, y0, vx, vy;
	cin >> n >> r >> h >> x0 >> y0 >> vx >> vy;
	long double d = std::abs(-vy * x0 + vx * y0) / std::sqrt(vx * vx + vy * vy);
	int sgn = (x0 * vx + y0 * vy >= 0) ? (-1) : 1;
	long double l1 = sgn * std::sqrt(x0 * x0 + y0 * y0 - d * d);
	long double l2 = std::sqrt(r * r - d * d);
	long double T0 = (l1 + l2) / std::sqrt(vx * vx + vy * vy);
	long double T = 2 * l2 / std::sqrt(vx * vx + vy * vy);
	long double ans_l = h / (T0 + n * T);
	long double ans_r = h / (T0 + (n - 1) * T);
	cout << ans_l << " " << ans_r << "\n";
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	cout << std::fixed << std::setprecision(10);
	// cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

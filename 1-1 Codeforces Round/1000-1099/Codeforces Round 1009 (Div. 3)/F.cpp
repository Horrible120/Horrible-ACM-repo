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

int get1side(int n, int k) {
	int ans = 0;
	for (int i = 1; i <= k; i *= 2) {
		if (n & i) {
			ans += k / i;
		}
	}
	return ans;
}

int get(int l1, int r1, int l2, int r2, int k) {
	if (l1 >= k || r1 <= 0 || l2 >= k || r2 <= 0) {
		return 0;
	}
	if (l1 <= 0 && r1 >= k && l2 <= 0 && r2 >= k) {
		return 1;
	}
	if (l1 <= 0 && r1 >= k && l2 <= 0) {
		return get1side(r2, k);
	}
	if (l1 <= 0 && r1 >= k && r2 >= k) {
		return get1side(k - l2, k);
	}
	if (l2 <= 0 && r2 >= k && l1 <= 0) {
		return get1side(r1, k);
	}
	if (l2 <= 0 && r2 >= k && r1 >= k) {
		return get1side(k - l1, k);
	}
	assert(k > 1);
	return get(l1, r1, l2, r2, k / 2) + get(l1, r1, l2 - k / 2, r2 - k / 2, k / 2) + get(l1 - k / 2, r1 - k / 2, l2, r2, k / 2) + get(l1 - k / 2, r1 - k / 2, l2 - k / 2, r2 - k / 2, k / 2);
}

void solve() {
	int l1, r1, l2, r2;
	cin >> l1 >> r1 >> l2 >> r2;
	cout << get(l1, r1, l2, r2, 1 << 20) << "\n";
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

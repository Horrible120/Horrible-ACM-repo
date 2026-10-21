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

const ll INF = 4e18, P = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	int n, m;
	std::cin >> n >> m;
	
	std::vector<std::vector<int>> g(n, std::vector<int>(m, 0));
	int cnt = 0;
	auto dfs = [&](auto &&self, int v, int i, int j) -> void {
		g[i][j] = v;
		if (j + 1 < m) {
			for (int w = 0; w < 4; ++w) {
				self(self, w, i, j + 1);
			}
		} else if (i + 1 < n) {
			for (int w = 0; w < 4; ++w) {
				self(self, w, i + 1, 0);
			}
		} else {
			for (int u = 0; u < n; ++u) {
				for (int v = 0; v < m; ++v) {
					if (u - 1 >= 0 && std::abs(g[u][v] - g[u - 1][v]) != 1) {
						return;
					}
					if (u + 1 < n && std::abs(g[u][v] - g[u + 1][v]) != 1) {
						return;
					}
					if (v - 1 >= 0 && std::abs(g[u][v] - g[u][v - 1]) != 1) {
						return;
					}
					if (v + 1 < m && std::abs(g[u][v] - g[u][v + 1]) != 1) {
						return;
					}
				}
			}
			++cnt;
			for (int u = 0; u < n; ++u) {
				for (int v = 0; v < m; ++v) {
					std::cout << (g[u][v] + 1) << " \n"[v == m - 1];
				}
			}
			std::cout << "\n";
		}
	};
	for (int w = 0; w < 4; ++w) {
		dfs(dfs, w, 0, 0);
	}
	std::cout << cnt << "\n";
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

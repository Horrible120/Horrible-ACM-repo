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
	
	std::vector<int> f(n, 0);
	std::vector<std::vector<int>> all;
	auto dfs = [&](auto &&self, int v, int i) -> void {
		f[i] = v;
		if (i + 1 < n) {
			if (v - 1 >= 0) {
				self(self, v - 1, i + 1);
			}
			if (v + 1 < 4) {
				self(self, v + 1, i + 1);
			}
		} else {
			all.push_back(f);
		}
	};
	for (int v = 0; v < 4; ++v) {
		dfs(dfs, v, 0);
	}
	int s = all.size();
	std::stable_sort(all.begin(), all.end());
	
	std::vector<std::vector<int>> g(s);
	int e = 0;
	for (int i = 0; i < s; ++i) {
		auto dfs1 = [&](auto &&self, int v, int j) -> void {
			f[j] = v;
			if (j + 1 < n) {
				if (v - 1 >= 0 && std::abs(v - 1 - all[i][j + 1]) == 1) {
					self(self, v - 1, j + 1);
				}
				if (v + 1 < 4 && std::abs(v + 1 - all[i][j + 1]) == 1) {
					self(self, v + 1, j + 1);
				}
			} else {
				int u = std::lower_bound(all.begin(), all.end(), f) - all.begin();
				g[i].push_back(u);
				g[u].push_back(i);
				e += 2;
			}
		};
		if (all[i][0] - 1 >= 0) {
			dfs1(dfs1, all[i][0] - 1, 0);
		}
	}
	
	std::cout << s << " " << e << " " << e / s << "\n";
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

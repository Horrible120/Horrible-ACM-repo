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
	int n, m, rs, cs;
	std::cin >> n >> m >> rs >> cs;
	--rs, --cs;
	
	if (n % 2 == 0) {
		std::vector<std::vector<char>> a(n, std::vector<char>(m, 0));
		a[0][0] = 'D';
		for (int j = 1; j < m; ++j) {
			a[0][j] = 'L';
		}
		for (int i = 1; i < n - 1; ++i) {
			if (i % 2 == 1) {
				a[i][0] = 'D';
				for (int j = 1; j < m - 1; ++j) {
					a[i][j] = 'R';
				}
				a[i][m - 1] = 'U';
			} else {
				a[i][0] = 'D';
				a[i][1] = 'U';
				for (int j = 2; j < m; ++j) {
					a[i][j] = 'L';
				}
			}
		}
		for (int j = 0; j < m - 1; ++j) {
			a[n - 1][j] = 'R';
		}
		a[n - 1][m - 1] = 'U';
		int rn = rs, cn = cs;
		for (int i = 0; i < n * m - 1; ++i) {
			std::string s;
			int r, c;
			std::cin >> r >> c;
			--r, --c;
			while (rn != r || cn != c) {
				char d = a[rn][cn];
				s.push_back(d);
				if (d == 'U') {
					--rn;
				} else if (d == 'D') {
					++rn;
				} else if (d == 'L') {
					--cn;
				} else if (d == 'R') {
					++cn;
				}
			}
			std::cout << s << std::endl;
		}
	} else if (m % 2 == 0) {
		std::vector<std::vector<char>> a(n, std::vector<char>(m, 0));
		a[0][0] = 'R';
		for (int i = 1; i < n; ++i) {
			a[i][0] = 'U';
		}
		for (int j = 1; j < m - 1; ++j) {
			if (j % 2 == 1) {
				a[0][j] = 'R';
				for (int i = 1; i < n - 1; ++i) {
					a[i][j] = 'D';
				}
				a[n - 1][j] = 'L';
			} else {
				a[0][j] = 'R';
				a[1][j] = 'L';
				for (int i = 2; i < n; ++i) {
					a[i][j] = 'U';
				}
			}
		}
		for (int i = 0; i < n - 1; ++i) {
			a[i][m - 1] = 'D';
		}
		a[n - 1][m - 1] = 'L';
		int rn = rs, cn = cs;
		for (int i = 0; i < n * m - 1; ++i) {
			std::string s;
			int r, c;
			std::cin >> r >> c;
			--r, --c;
			while (rn != r || cn != c) {
				char d = a[rn][cn];
				s.push_back(d);
				if (d == 'U') {
					--rn;
				} else if (d == 'D') {
					++rn;
				} else if (d == 'L') {
					--cn;
				} else if (d == 'R') {
					++cn;
				}
			}
			std::cout << s << std::endl;
		}
	} else {
		std::vector<std::vector<char>> a(n, std::vector<char>(m, 0));
		a[0][0] = 'D';
		a[0][1] = 'L';
		a[0][2] = 'L';
		for (int j = 3; j < m; ++j) {
			if (j % 2 == 1) {
				a[0][j] = 'D';
			} else {
				a[0][j] = 'L';
			}
		}
		a[1][0] = 'D';
		a[1][1] = 'U';
		a[1][2] = '*';
		for (int j = 3; j < m; ++j) {
			if (j % 2 == 1) {
				a[1][j] = 'L';
			} else {
				a[1][j] = 'U';
			}
		}
		for (int i = 2; i < n - 1; ++i) {
			if (i % 2 == 1) {
				a[i][0] = 'D';
				a[i][1] = 'U';
				for (int j = 2; j < m; ++j) {
					a[i][j] = 'L';
				}
			} else {
				a[i][0] = 'D';
				for (int j = 1; j < m - 1; ++j) {
					a[i][j] = 'R';
				}
				a[i][m - 1] = 'U';
			}
		}
		for (int j = 0; j < m - 1; ++j) {
			a[n - 1][j] = 'R';
		}
		a[n - 1][m - 1] = 'U';
		int rn = rs, cn = cs;
		for (int i = 0; i < n * m - 1; ++i) {
			std::string s;
			int r, c;
			std::cin >> r >> c;
			--r, --c;
			while (rn != r || cn != c) {
				char d = a[rn][cn];
				if (d == '*') {
					if (r == 1 && c == 1) {
						d = 'L';
					} else if (r == 0 && c == 2) {
						d = 'U';
					} else {
						d = 'L';
					}
				}
				s.push_back(d);
				if (d == 'U') {
					--rn;
				} else if (d == 'D') {
					++rn;
				} else if (d == 'L') {
					--cn;
				} else if (d == 'R') {
					++cn;
				}
			}
			std::cout << s << std::endl;
		}
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

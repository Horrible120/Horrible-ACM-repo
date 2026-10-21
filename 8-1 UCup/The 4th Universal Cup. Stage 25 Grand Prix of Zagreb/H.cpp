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
	std::string s;
	std::cin >> s;
	
	int n = s.size();
	std::vector<int> f(n, 0);
	int r = 0;
	for (int j = n - 2; j >= 0; --j) {
		if (s[j + 1] < s[j]) {
			r = 1;
		} else if (s[j + 1] > s[j]) {
			r = 0;
		}
		f[j + 1] += r;
	}
	for (int i = 1; i < n; ++i) {
		f[i] += f[i - 1];
	}
	std::vector<int> next(n, n);
	for (int i = n - 2; i >= 0; --i) {
		if (s[i + 1] != s[i]) {
			next[i] = i + 1;
		} else {
			next[i] = next[i + 1];
		}
	}
	for (int i = 0; i < n; ++i) {
		if (next[i] < n && s[next[i] - 1] < s[next[i]]) {
			f[i] += (n - next[i]);
		}
	}

	std::vector<int> p(n, 0);
	std::iota(p.begin(), p.end(), 0);
	std::stable_sort(p.begin(), p.end(), [&](int u, int v) -> bool {
		return f[u] < f[v];
	});
	int x = 0;
	while (x < n && f[p[x]] <= (n - 1) / 2) {
		++x;
	}
	--x;
	for (int j = 0; j < p[x]; ++j) {
		std::cout << s[j];
	}
	for (int j = p[x] + 1; j < n; ++j) {
		std::cout << s[j];
	}
	std::cout << "\n";
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

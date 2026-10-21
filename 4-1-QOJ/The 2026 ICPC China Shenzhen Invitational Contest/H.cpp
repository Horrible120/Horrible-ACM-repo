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

void first() {
	int n, k;
	std::cin >> n >> k;
	
	std::vector<int> f(n + 1, 0);
	for (int i = 0; i < k; ++i) {
		int a;
		std::cin >> a;
		f[a] = 1;
	}
	
	int ans = -1;
	std::vector<int> s;
	for (int i = 1; i <= n; ++i) {
		if (f[i]) {
			s.push_back(i);
		} else {
			if (!s.empty()) {
				s.pop_back();
			} else {
				ans = i;
			}
		}
	}
	f[ans] = 1;
	
	std::vector<int> res;
	for (int i = 1; i <= n; ++i) {
		if (f[i]) {
			res.push_back(i);
		}
	}
	
	for (int i = 0; i < k + 1; ++i) {
		std::cout << res[i] << " \n"[i == k];
	}
}

void second() {
	int n, k;
	std::cin >> n >> k;
	
	std::vector<int> f(n + 1, 0);
	for (int i = 0; i < k + 1; ++i) {
		int a;
		std::cin >> a;
		f[a] = 1;
	}
	
	std::vector<int> s;
	for (int i = 1; i <= n; ++i) {
		if (f[i]) {
			s.push_back(i);
		} else {
			if (!s.empty()) {
				s.pop_back();
			}
		}
	}
	std::cout << s[0] << "\n";
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	std::string s;
	std::cin >> s;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	if (s == "Alice") {
		while ( tt-- ) {
			first();
	//		cout.flush();
		}
	} else {
		while ( tt-- ) {
			second();
			//		cout.flush();
		}
	}
	cout.flush();
	
	return 0;
}

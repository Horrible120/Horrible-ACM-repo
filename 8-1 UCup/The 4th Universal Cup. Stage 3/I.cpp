#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long long i64;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;
void solve() {
    int n;
    std::cin >> n;

    std::vector<int> pw(n + 1, 0);
    std::vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
        pw[p[i]]=i;
    }

    std::vector<int> qw(n + 1, 0);
    std::vector<int> q(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> q[i];
        qw[q[i]]=i;
    }

    bool pd=1;
    std::vector<pair<int,int>> cz;
    for (int y = n; y >= 1; y--){
        if( pw[y] == qw[y] ) {
            continue;
        } else if (pw[y] < qw[y]) {
            std::cout << "NO\n";
            return;
        } else {
            cz.push_back( make_pair( qw[y] , pw[y] ) );
            int old1 = p[qw[y]];
            int old2 = p[pw[y]];
            std::swap(p[qw[y]], p[pw[y]]);
            std::swap(pw[old1], pw[old2]);
        }
    }
    assert(p == q);
    std::cout << "YES\n";

    std::cout << cz.size() << "\n";
    for(auto [i, j]:cz){
        std::cout << i << " " << j << "\n";
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
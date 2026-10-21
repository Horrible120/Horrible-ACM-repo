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

struct DSU {
    std::vector<int> f, siz;
    int cnt;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        cnt = n;
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }
        siz[x] += siz[y];
        f[y] = x;
        cnt -= 1;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::set<std::array<int, 2>> e;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        if (u > v) {
            std::swap(u, v);
        }
        e.insert({u, v});
    }

    int x = 0, y = 0;
    std::vector<std::array<int, 3>> del;

    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        int u = (x + a) % n;
        int v = (y + b) % n;
        if (u > v) {
            std::swap(u, v);
        }
        auto it = e.find({u, v});
        if (it != e.end()) {
            del.push_back({u, v, i});
            e.erase(it);
        }
        x = (2 * x + 1) % n;
        y = (3 * y + 1) % n;
    }

    DSU d(n);
    for (auto [u, v] : e) {
        d.merge(u, v);
    }

    int now = q - 1;
    std::vector<int> c(q, 0);
    for (int i = (int)del.size() - 1; i >= 0; --i) {
        auto [u, v, time] = del[i];
        while (now >= time) {
            c[now] = (d.cnt == 1);
            --now;
        }
        d.merge(u, v);
    }
    while (now >= 0) {
        c[now] = (d.cnt == 1);
        --now;
    }
    for (int i = 0; i < q; ++i) {
        std::cout << c[i] << "\n";
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
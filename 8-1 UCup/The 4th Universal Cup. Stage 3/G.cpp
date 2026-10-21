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
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
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
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<int>> g(n);
    DSU d(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
        d.merge(u, v);
    }

    std::vector<int> f(n, 0);
    std::iota(f.begin(), f.end(), 0);
    std::shuffle(f.begin(), f.end(), rnd);
    
    std::array<std::vector<i64>, 300> dis;
    for (int i = 0; i < 300 && i < n; ++i) {
        int s = f[i];
        dis[i].assign(n, INF);
        std::vector<int> vis(n, 0);
        std::queue<int> q;
        dis[i][s] = 0;
        vis[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!vis[v]) {
                    dis[i][v] = dis[i][u] + 1;
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        if (!d.same(x, y)) {
            std::cout << "YES\n";
            continue;
        }
        int s = d.siz[d.find(x)];
        if (s <= 20000) {
            std::cout << "NO\n";
            continue;
        }
        i64 min = INF;
        for (int i = 0; i < 300 && i < n; ++i) {
            min = std::min(min, dis[i][x] + dis[i][y]);
        }
        if (min > 20000) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
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
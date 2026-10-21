#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef uint64_t ull;

ll tt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> tt;

	while (tt--) {
		ll n, m;
		cin >> n >> m;
		if (m == 0)

		{
			cout << 0 << endl;
			continue;
		}

		vector<tuple<ll, ll, ll>> ans;
		vector<set<ll>> edge(n + 1);

		ll u, v;
		for (int i = 1; i <= m; i++) {
			cin >> u >> v;
			edge[u].insert(v);
			edge[v].insert(u);
		}

		ll fir, sec;
		for (int i = 1; i <= n; i++) {
			while (edge[i].size() >= 2) {
				fir = *edge[i].begin();
				edge[i].erase(edge[i].begin());
				edge[fir].erase(i);

				sec = *edge[i].begin();
				edge[i].erase(edge[i].begin());
				edge[sec].erase(i);

				if (edge[fir].contains(sec)) {
					edge[fir].erase(sec);
					edge[sec].erase(fir);
				} else {
					edge[fir].insert(sec);
					edge[sec].insert(fir);
				}
				ans.push_back({fir, sec, i});
			}
		}

//		for(int i=1;i<=n;i++){
//			for(auto &x :edge[i])
//			cout<<i<<' '<<x<<endl;
//		}

		vector<pair<ll, ll>> p;
		vector<ll> s;
		for (int i = 1; i <= n; i++) {
			if (!edge[i].size())
				s.push_back(i);
			else if (*edge[i].begin() > i)
				p.push_back({i, *edge[i].begin()});
		}

//		for(auto i:s){
//			cout<<i<<endl;
//		}

		if (!p.empty()) {
			auto [x, y] = p.back();
			p.pop_back();
			for (auto &i : s) {
				ans.push_back({i, x, y});
				y = i;
			}
			for (auto &[u, v] : p) {
				ans.push_back({x, u, v});
			}
		}
		cout << ans.size() << endl;
		for (auto &[x, y, z] : ans) {
			cout << x << ' ' << y << ' ' << z << endl;
		}
	}

	return 0;
}

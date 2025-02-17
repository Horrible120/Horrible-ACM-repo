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
#define OO cout<<">>>>";

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
         Mod = 1e9+7;

ll tt;


int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;

	while ( tt-- ) {
		ll n, m, k;
		cin >> n >> m >> k;
		vector<ll> h(n + 1), x(n + 1);

		for (ll i = 1; i <= n; i++)
			cin >> h[i];

		for (ll i = 1; i <= n; i++)
			cin >> x[i];

		ll l = 1, r = 1e9+1, mid, ans = 1e9+1;

		while (l <= r) {
			mid = (l + r) / 2;

			vector<pair<ll, ll>> g;

			for (ll i = 1; i <= n; i++)
				if ((h[i] + mid - 1) / mid <= m) {
					g.emplace_back(make_pair(max(1ll, x[i] - (m - (h[i] + mid - 1) / mid)), 1));
					g.emplace_back(make_pair(x[i] + (m - (h[i] + mid - 1) / mid) + 1, -1));
				}

			sort(g.begin(), g.end());
//			OO cout<<mid<<endl;
//			for(auto [x,y]:g)
//				cout<<x<<' '<<y<<endl;

			ll cnt = 0, flag = 0;

			for (auto [x, y] : g) {
				cnt += y;

				if (cnt >= k)
					break;
			}

			if (cnt >= k)
				ans = min(ans, mid), r = mid - 1;
			else
				l = mid + 1;
		}

//		OO
		if (ans > 1e9)
			cout << -1 << endl;
		else
			cout << ans << endl;
	}

	return 0;
}

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

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
         Mod = 998244353;

const ll MAXN = 1e6+1;

ll n;
ll mob[1000010], pr[1000010], a[200010], dp[1000010];

void init2() {
	bool np[1000010] = {};		//not_prime 数组
	vector<ll> prm;				//素数序列

	for (ll i = 1; i <= MAXN; i++)
		mob[i] = 1;				//初始化 莫比乌斯函数 数组

	np[1] = 1;
	mob[1] = 1;

	for (ll i = 2; i <= MAXN; i++) {
		if (!np[i]) {
			mob[i] = -1;
			pr[i] = i;			//素数在最小素因子是他本身
			prm.emplace_back(i);
		}

		for (auto j : prm) {

			if (j * i > MAXN) break;

			np[i *j] = 1;
			pr[i *j] = j;

			if (i % j == 0) {
				mob[i *j] = 0;
				break;
			}

			mob[i *j] = -mob[i];
		}
	}

	mob[1] = 0;
	pr[1] = 1;
//	for(ll i=1;i<=50;i++){
//		cout<<i<<' '<<pr[i]<<' '<<mob[i]<<endl;
//	}
}

void init() {
	for (ll i = 1; i <= MAXN; i++)
		pr[i] = i, mob[i] = 1;

	for (ll i = 2; i <= MAXN; i++) {
		if (pr[i] == i) {
			for (ll j = i; j <= MAXN; j += i)
				pr[j] = min(pr[j], i);

			mob[i] = -1;
		}

	}

	mob[1] = 1;

	for (ll i = 2; i <= MAXN; i++) {
		if (pr[i] == pr[i / pr[i]])
			mob[i] = 0;
		else
			mob[i] = mob[i / pr[i]] * mob[pr[i]];
	}

	mob[1] = 0;
//	for(ll i=1;i<=100;i++)
//		cout<<i<<' '<<mob[i]<<endl;
}

ll DFS(vector<ll> &v, ll st, ll w) {

	if (w == v.size()) {
		if (st == 1) return 0;

//		cout<<"!!"<<st<<' '<<dp[st]<<endl;
		return dp[st] * (-mob[st]);
	}

	return (DFS(v, st, w + 1) + DFS(v, st *v[w], w + 1)) % Mod;
}

void change(vector<ll> &v, ll st, ll w, ll ans) {
	if (w == v.size()) {
		if (st == 1) return;

//		cout<<st<<' '<<ans<<endl;
		dp[st] = (dp[st] + ans) % Mod;
		return;
	}

	change(v, st, w + 1, ans);
	change(v, st *v[w], w + 1, ans);
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> n;
	init2();

	for (ll i = 1; i <= n; i++)
		cin >> a[i];

	for (ll i = 1; i <= n; i++) {
		ll x = a[i], ans = 0;
		vector<ll> v;

		while (x > 1) {
			if (v.empty() || *v.rbegin() != pr[x])
				v.emplace_back(pr[x]);

			x /= pr[x];
		}

		if (i == 1) {
			change(v, 1, 0, 1);
			continue;
		}

		ans = DFS(v, 1, 0);
		change(v, 1, 0, ans);

//		cout<<">>>>>>"<<ans<<endl;
		if (i == n)
			cout << (ans + Mod) % Mod << endl;
	}

	return 0;
}

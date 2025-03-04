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
         Mod = 1e9+7;

struct Node {
	ll co, fa, M, m;
};

ll tt;
ll n, q;
Node node[500010];
map<ll, ll> mp;

ll get_fa(ll x) {
	if (node[x].fa == x)
		return x;
	else
		return node[x].fa = get_fa(node[x].fa);
}

void join(ll a, ll b) {
	a = get_fa(a);
	b = get_fa(b);

	if (a == b)
		return;

	node[b].fa = a;
	node[a].M = max(node[a].M, node[b].M);
	node[a].m = min(node[a].m, node[b].m);
}

void change(ll x, ll c) {
	x = get_fa(x);
	mp[node[x].co] -= node[x].M - node[x].m + 1;
	node[x].co = c;
	mp[c] += node[x].M - node[x].m + 1;

	if (node[x].M < n && node[get_fa(node[x].M + 1)].co == c)
		join(get_fa(node[x].M + 1), x);

	if (node[x].m > 1 && node[get_fa(node[x].m - 1)].co == c)
		join(get_fa(node[x].m - 1), x);
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> n >> q;

	for (int i = 1; i <= n; i++)
		node[i].fa = node[i].co = node[i].M = node[i].m = i,
		       mp[i] = 1;

	ll op, a, b;

	for (int i = 1; i <= q; i++) {
		cin >> op;

		if (op == 1) {
			cin >> a >> b;
			change(a, b);
		}

		if (op == 2) {
			cin >> a;
//			cout<<">>";
			cout << mp[a] << endl;
		}
	}

	return 0;
}

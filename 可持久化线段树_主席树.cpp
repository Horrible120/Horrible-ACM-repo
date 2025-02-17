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

const ll INF = 1e10,
         Mod = 1e9+7;

ll cnt = 0;
ll n, m;
ll a[600010];
ll root[200010];

struct Node {
	ll lson, rson, cnt;
	Node() {}
} tr[7000010];

void add_node(ll &x, ll pre, ll l, ll r, ll key) {	//重点：和一般的权值线段树的建点不一样
													//需要做原来部分子节点的继承
	if (!x) x = ++cnt;

	tr[x].cnt = tr[pre].cnt + 1;	//并不完全是这样，如果涉及删除数字或者其他更改就应该细化对应的操作
	tr[x].lson = tr[pre].lson;
	tr[x].rson = tr[pre].rson;

	if (l == r) return;

	ll mid = l + ((r - l) >> 1);

	if (key <= mid) {
		tr[x].lson = 0;
		add_node(tr[x].lson, tr[pre].lson, l, mid, key);
	} else {
		tr[x].rson = 0;
		add_node(tr[x].rson, tr[pre].rson, mid + 1, r, key);
	}

	//cout<<">> Node["<<x<<"]: "<<tr[x].lson<<' '<<tr[x].rson<<' '<<tr[x].cnt<<endl;
}

ll query(Node &u, Node &v, ll l, ll r, ll k) {	//查询区间k小值
	if (l == r)
		return l;

	ll x = tr[v.lson].cnt - tr[u.lson].cnt;
	ll mid = l + ((r - l) >> 1);

	if (k <= x)
		return query(tr[u.lson], tr[v.lson], l, mid, k);
	else
		return query(tr[u.rson], tr[v.rson], mid + 1, r, k - x);
}

int main() {
//	ios::sync_with_stdio( 0 );
//	cin.tie( 0 );
//	cout.tie( 0 );

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	root[0] = 0;

	for (int i = 1; i <= n; i++) {
		root[i] = ++cnt;
		add_node(root[i], root[i - 1], 0, INF, a[i]);
	}

	ll l, r, k;

	for (int i = 1; i <= m; i++) {
		cin >> l >> r >> k;
		cout << query(tr[root[l - 1]], tr[root[r]], 0, INF, k) << endl;
	}

	return 0;
}

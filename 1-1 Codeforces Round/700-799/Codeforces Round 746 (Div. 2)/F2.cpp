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
	ll n,m;
	cin >> n >> m;
	vector<vector<ll>> val(n+2,vector<ll>(m+2)),dif=val;
	for (ll i=1;i<=n;i++) {
		string s;
		cin >> s;
		for (ll j=1;j<=m;j++)
			val[i][j]=(s[j-1]=='B');
	}

	ll ans=0;
	for (ll i=1;i<=n;i++)
		for (ll j=1;j<=m;j++) {
			dif[i][j]=val[i][j]^val[i+1][j]^val[i][j+1]^val[i+1][j+1];
			ans+=dif[i][j];
		}

	vector<vector<ll>> eg(n+1);
	for (ll i=1;i<n;i++)
		for (ll j=1;j<m;j++)
			if (dif[i][j] && dif[i][m] && dif[n][j])
				eg[i].emplace_back(j);

	vector<ll> mat(n+1),rev(m+1),dis(n+1),cur(n+1);
	auto bfs=[&]()->bool{
		queue<ll> que;
		fill(dis.begin(),dis.end(),INF);
		for (ll i=1;i<n;i++)
			if (!mat[i]) {
				dis[i]=0;
				que.emplace(i);
			}
		while (!que.empty()) {
			ll u=que.front();
			que.pop();
			if (dis[u]>=dis[0])
				continue;
			for (ll v:eg[u]) {
				ll nxt=rev[v];
				if (dis[nxt]==INF) {
					dis[nxt]=dis[u]+1;
					if (nxt)
						que.emplace(nxt);
				}
			}
		}
		return dis[0]!=INF;
	};
	auto dfs=[&](this auto &&self,ll u)->bool{
		if (!u)
			return true;
		for (ll &i=cur[u];i<(ll)eg[u].size();i++) {
			ll v=eg[u][i];
			if (dis[rev[v]]==dis[u]+1 && self(rev[v])) {
				mat[u]=v;
				rev[v]=u;
				return true;
			}
		}
		dis[u]=INF;
		return false;
	};

	ll cnt=0;
	while (bfs()) {
		fill(cur.begin(),cur.end(),0);
		for (ll i=1;i<n;i++)
			if (!mat[i] && dfs(i))
				cnt++;
	}
	cout << ans-cnt+(cnt%2)*(1-2*dif[n][m]) << '\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}

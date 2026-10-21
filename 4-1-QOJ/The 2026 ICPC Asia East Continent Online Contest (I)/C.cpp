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
	cin>>n>>m;

	v2ct<ll> e(n+1);
	vector<ll> deg(n+1),ans(n+1);
	for(ll i=1;i<=m;i++){
		ll l,r,u;
		cin>>l>>r>>u;
		for(ll j=l;j<r;j++){
			ll v;
			cin>>v;
			e[u].push_back(v);
			deg[v]++;
			u=v;
		}
	}

	std::priority_queue<ll,vector<ll>,greater<ll>> que;
	for(ll i=1;i<=n;i++){
		if(!deg[i]) que.push(i);
	}

	ll cnt=0;
	while(!que.empty()){
		ll u=que.top();
		que.pop();
		ans[u]=++cnt;
		for(ll i=0;i<(ll)e[u].size();i++){
			ll v=e[u][i];
			deg[v]--;
			if(!deg[v]) que.push(v);
		}
	}

	if(cnt<n){
		cout<<-1<<'\n';
		return;
	}
	for(ll i=1;i<=n;i++) cout<<ans[i]<<(i==n?'\n':' ');
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

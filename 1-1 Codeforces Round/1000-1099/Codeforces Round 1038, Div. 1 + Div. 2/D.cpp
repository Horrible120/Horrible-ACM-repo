#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> eg(n+1);
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> dp(n+1,INF);
	
	dp[1]=0;
	for(ll i=0;i<3*n;i++){
		vector<ll> tmp(n+1,INF);
		for(ll j=1;j<=n;j++){
			tmp[j]=min(tmp[j],dp[j]+1);
			if(dp[j]<INF){
				ll v=eg[j][i%eg[j].size()];
				tmp[v]=min(tmp[v],dp[j]);
			}
		}
		dp=tmp;
		if(dp[n]<INF){
//			OOO
			cout<<i+1<<' '<<dp[n]<<endl;
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

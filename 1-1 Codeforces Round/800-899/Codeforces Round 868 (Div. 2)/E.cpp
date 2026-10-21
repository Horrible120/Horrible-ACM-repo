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
	ll n;
	cin>>n;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	ll l,r;
	cin>>l>>r;
	
	for(ll i=1;i<=n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> vis(n+1,0);
	
	ll m=0;
	vector<ll> cnt(n+1,0);
	
	for(ll i=1;i<=n;i++) if(!vis[i]){
		ll tmp=i;
		m++;
		while(!vis[tmp]){
			vis[tmp]=true;
			cnt[m]++;
			for(auto v:eg[tmp]) if(!vis[v]) tmp=v;
		}
	}
	
	ll ans=0;
	
	for(ll i=1;i<=m;i++){
		if(cnt[i]<l+r) ans^=cnt[i]/l;
	}
	
	cout<<(ans?"Alice":"Bob")<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

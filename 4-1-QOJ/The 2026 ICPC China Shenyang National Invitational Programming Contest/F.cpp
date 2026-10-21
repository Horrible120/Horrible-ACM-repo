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
	vector<vector<ll>> ans(n+1,vector<ll>(n+1,0));
	
	for(ll i=1;i<=n-1;i++){
		ans[1][i]=i;
	}
	
	ans[1][n]=0;
	
	for(ll i=2;i<=n;i++){
		ans[i][n]=i+n-2;
	}
	
	ll cnt=2*n-2;
	
	for(ll i=2;i<=n;i++){
		for(ll j=1;j<=n-1;j++){
			ans[i][j]=++cnt;
		}
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			cout<<ans[i][j]<<' ';
		}
		cout<<'\n';
	}
	
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

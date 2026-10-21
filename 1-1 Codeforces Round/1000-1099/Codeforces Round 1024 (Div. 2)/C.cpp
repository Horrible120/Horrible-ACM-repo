#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	
	v2ct<ll> ans(n+1,vector<ll>(n+1,0));
	
	for(ll i=1;i<=n;i+=2){
		ll cur=(n-i+1)*(n-i+1)-1;
		ll k=(i+1)/2;
		for(ll x=k,y=k;x<=n+1-k;x++)
			ans[x][y]=cur--;
		for(ll x=n+1-k,y=k+1;y<=n+1-k;y++)
			ans[x][y]=cur--;
		for(ll x=n-k,y=n+1-k;x>=k;x--)
			ans[x][y]=cur--;
		for(ll x=k,y=n-k;y>k;y--)
			ans[x][y]=cur--;
	}
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			cout<<ans[i][j]<<" \n"[j==n];
	cout.flush();
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

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
	ll n,ans=INF;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector dp1(n+2,vector<ll>(10,0)),dp2(n+2,vector<ll>(10,0));
	
	for(ll i=1;i<=n;i++){
		ll tmp=INF;
		for(ll j=0;j<=9;j++){
			tmp=min(tmp,dp1[i-1][j]);
			dp1[i][j]=tmp+min(abs(v[i]-j),10-abs(v[i]-j));
		}
	}
	
	for(ll i=n;i>=1;i--){
		ll tmp=INF;
		for(ll j=0;j<=9;j++){
			tmp=min(tmp,dp2[i+1][j]);
			dp2[i][j]=tmp+min(abs(v[i]-j),10-abs(v[i]-j));
		}
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<=9;j++){
			ans=min(ans,dp1[i][j]+dp2[i][j]-min(abs(v[i]-j),10-abs(v[i]-j)));
		}
	}
	
	cout<<ans<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

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
	vector<ll> w(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>w[i];
	}
	
	vector dp(n+1,vector<ll>(m+1,0));
	
	dp[0][0]=1;
	
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<=m;j++){
			if(w[i]<=j){
				dp[i][j]=(dp[i-1][j]+dp[i-1][j-w[i]])%10;
			}else{
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	
	vector<ll> ans(m+1,0);
	
	for(ll i=1;i<=n;i++){
		string s;
		ans[0]=1;
		for(ll j=1;j<=m;j++){
			if(j<w[i]){
				ans[j]=dp[n][j];
			}else{
				ans[j]=(dp[n][j]-ans[j-w[i]]+10)%10;
			}
			s+=(char)('0'+ans[j]%10);
		}
		cout<<s<<endl;
	}
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

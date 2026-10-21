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
	ll n,m,r;
	cin>>n>>m>>r;
	vector<vector<vector<ll>>> dp(n+1,vector<vector<ll>>(m+1,vector<ll>(r+1,0)));
	auto atk=dp;
	dp[0][0][0]=1;
	for(ll i=1;i<=r;i++){
		ll t,d,c;
		cin>>t>>d>>c;
//		OOO
		if(d==1){
			for(ll j=0;j<=m;j++){
				if(t-c-j>=0&&t-c-j<=r){
					atk[c][j][t-c-j]=1;
				}
			}
		}else{
			for(ll j=0;j<=n;j++){
				if(t-c-j>=0&&t-c-j<=r){
					atk[j][c][t-c-j]=1;
				}
			}
		}
	}
	
	for(ll k=0;k<=r;k++){
		for(ll i=0;i<=n;i++){
			for(ll j=0;j<=m;j++){
				
				if(k>0) dp[i][j][k]|=dp[i][j][k-1];
				if(j>0) dp[i][j][k]|=dp[i][j-1][k];
				if(i>0) dp[i][j][k]|=dp[i-1][j][k];
				
				if(atk[i][j][k]){
					dp[i][j][k]=0;
				}
			}
				
		}
		if(dp[n][m][k]){
//			OOO
			cout<<n+m+k<<endl;
			return;
		}
	}
//	OOO
	cout<<-1<<endl;
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

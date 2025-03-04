#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> pos(n+1),v(n+1);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		pos[v[i]]=i;
	}
	
	v2ct<ll> dp(n+1,vector<ll>(n+1,INF));
	
	for(ll i=1;i<=n;i++) dp[i][i]=0;
//	for(ll i=1;i<n;i++) dp[i+1][i]=abs(pos[i]-pos[i+1]);
	
	for(ll i=2;i<=n;i++){
//		cout<<"Here"<<endl;
		for(ll j=i-1;j>=1;j--){
			for(ll k=i-1;k>=j;k--){
				dp[i][j]=min(dp[i][j],dp[i-1][k]+dp[k][j]+abs(pos[i]-pos[k]));
				
			}
//			cout<<'['<<i<<','<<j<<']'<<dp[i][j]<<"  ";
		}
//		cout<<endl;
	}
//	OOO
	cout<<dp[n][1]<<endl;
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

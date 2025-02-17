#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	vector<vector<ll>> mp(n+1,vector<ll>(m+1)),dp(n+1,vector<ll>(m+1,INF)),pre(n+1,vector<ll>(m+1));
	
	vector<vector<vector<ll>>> tl(n+1,vector<vector<ll>>(m+1,vector<ll>(m+1,INF)));
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			cin>>mp[i][j];

	dp[0][1]=0;
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			pre[i][j]=pre[i][j-1]+mp[i][j];
	
	for(ll i=1;i<=n;i++){
		for(ll len=1;len<=m;len++){
			
			multiset<ll> s1,s2;
			vector<ll> w(m+1);
			for(ll j=1;j<=m;j++){
				if(j+len-1<=m) w[j]=pre[i][j+len-1]-pre[i][j-1];
				else w[j]=pre[i][m]-pre[i][j-1]+pre[i][j+len-1-m];
			}
			
			for(ll j=1;j<=m;j++)
				s1.insert(w[j]+(j-1)*k);
			
			for(ll l=1;l+len-1<=m;l++){
				tl[i][l][l+len-1]=min((s1.size()?(*s1.begin()):INF)-(l-1)*k,(s2.size()?(*s2.begin()):INF)-l*k);
				s1.erase(s1.find(w[l]+(l-1)*k));
				s2.insert(w[l]+(m+l)*k);
//				cout<<"!!! "<<i<<' '<<l<<' '<<' '<<l+len-1<<" : "<<tl[i][l][l+len-1]<<endl;
			}
		}
	}
	
	for(ll i=1;i<=n;i++)
		for(ll l=1;l<=m;l++)
			for(ll r=l;r<=m;r++)
				dp[i][r]=min(dp[i][r],dp[i-1][l]+tl[i][l][r]);
//	OOO
	cout<<dp[n][m]<<endl;
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

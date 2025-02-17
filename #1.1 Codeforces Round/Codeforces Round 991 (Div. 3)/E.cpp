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

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		string a,b,c;
		cin>>a>>b>>c;
		vector<vector<ll>> dp(a.size()+1,vector<ll>(b.size()+1,0));
		for(ll i=0;i<=a.size();i++){
			for(ll j=0;j<=b.size();j++){
				if(j) dp[i][j]=dp[i][j-1]+(c[i+j-1]==b[j-1]);
				if(i) dp[i][j]=max(dp[i][j],dp[i-1][j]+(c[i+j-1]==a[i-1]));
//				cout<<dp[i][j]<<' ';
			}
//			cout<<endl;
		}
			
//		OOO
		cout<<c.size()-dp[a.size()][b.size()]<<endl;	
	}
	
	cout.flush();
	
	return 0;
}

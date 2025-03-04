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
	v2ct<ll> ans(n+1,vector<ll>(n+1));
	for(ll i=1;i<=(n+1)/2;i++){
		for(ll x=i;x<=n+1-i;x++)
			for(ll y=i;y<=n+1-i;y++)
				ans[x][y]=i%2;
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			if(ans[i][j]==1) cout<<'#';
			else cout<<".";
		}
		cout<<endl;
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

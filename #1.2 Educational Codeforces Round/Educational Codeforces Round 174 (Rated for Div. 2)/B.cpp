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
	ll n,m,flag1=0,flag2=0;
	cin>>n>>m;
	v2ct<ll> mp(n+2,vector<ll>(m+2,0));
	map<ll,ll> ct;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			cin>>mp[i][j],ct[mp[i][j]]=1;
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			if(mp[i][j]==mp[i+1][j]||
				mp[i][j]==mp[i-1][j]||
				mp[i][j]==mp[i][j+1]||
				mp[i][j]==mp[i][j-1]) ct[mp[i][j]]=2,flag2=1;
		}
	ll ans=0;
	for(auto [x,cnt]:ct){
		ans+=cnt;
	}
	if(flag2) ans-=2;
	else ans-=1;
//	OOO
	cout<<ans<<endl;
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

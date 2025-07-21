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
	ll n=0,m=0,ans=0;
	cin>>n>>m;
	
	vector<ll> cnt(m+1,0);
	vector<vector<ll>> value(m+1);
	vector<vector<array<ll,3>>> elm(m+1);
	for(ll i=1;i<=n;i++){
		ll th,ts,td;
		cin>>th>>ts>>td;
		cnt[ts]++;
		elm[ts].emplace_back(array<ll,3>({ts,th,td}));
		value[ts].emplace_back(0);
	}
	
	for(ll u=0;u<=m;u++){
		ll tmpm=m-u;
		vector<ll> dp(m+1,-INF);
		dp[0]=0;
		
		for(ll i=1;i<=tmpm;i++){
			for(ll j=0;j<cnt[i];j++){
				value[i][j]=elm[i][j][1]-u*elm[i][j][2];
			}
			nth_element(value[i].begin(),value[i].begin()+min(cnt[i],tmpm/i),value[i].begin()+cnt[i],greater<ll>());
			ll siz=min(cnt[i],tmpm/i);
			for(ll j=0;j<siz;j++){
				for(ll k=tmpm;k>=i;k--){
					dp[k]=max(dp[k],dp[k-i]+value[i][j]);
				}
			}
		}
		ans=max(ans,dp[tmpm]);
	}
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

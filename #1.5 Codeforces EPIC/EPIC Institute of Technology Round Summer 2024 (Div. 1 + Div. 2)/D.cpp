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
	ll n;
	cin>>n;
	vector<ll> v(n+1),cnt(n+1);
	ll tot=0;
	for(ll i=1;i<=n;i++) cin>>v[i];
	sort(v.begin()+1,v.end());
	for(ll i=1;i<=n;i++){
		if(v[i]>v[i-1]) cnt[++tot]=1;
		else cnt[tot]++;
	}
	
	vector<vector<ll>> dp(tot+1,vector<ll>(tot+1,-1));
	
	function<ll(ll,ll)> DFS=[&](ll x,ll c){
		if(x>tot) return 0ll;
		if(~dp[x][c]) return dp[x][c];
		
		ll res=DFS(x+1,c+1)+1;	
		//为什么？？？
		
		if(c>=cnt[x]) res=min(res,DFS(x+1,c-cnt[x]));
		return dp[x][c]=res;
	};
//	OOO
	cout<<DFS(1,0)<<endl;
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

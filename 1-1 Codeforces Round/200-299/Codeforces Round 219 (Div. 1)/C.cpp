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
	ll n,m,d;
	cin>>n>>m>>d;
	vector<ll> a(m+1,0),b(m+1,0),t(m+1,0);
	
	for(ll i=1;i<=m;i++){
		cin>>a[i]>>b[i]>>t[i];
	}
	
	vector<ll> dp(n+1,0),g(n+1,0);
	
	vector<pll> stk(n+1);
	ll tail,head;
	
	for(ll i=1;i<=m;i++){
		ll len=(t[i]-t[i-1])*d;
		tail=1,head=0;
		
		ll r=1;
		
		for(ll j=1;j<=n;j++){
			while(r<=min(n,j+len)){
				while(head>=tail&&stk[head].second<=dp[r]) head--;
				stk[++head]=make_pair(r,dp[r]);
				r++;
			}
			while(head>=tail&&stk[tail].first<max(1ll,j-len)) tail++;
			dp[j]=stk[tail].second+b[i]-abs(a[i]-j);
		}
	}
	
	ll ans=-INF;
	for(ll i=1;i<=n;i++) ans=max(ans,dp[i]);
	
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

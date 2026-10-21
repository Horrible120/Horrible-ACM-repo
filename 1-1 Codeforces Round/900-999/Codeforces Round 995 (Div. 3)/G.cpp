#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q,ans=INF;
	cin>>n>>q;
	vector<pll> evt;
	vector<ll> cnt_p(n+1,0),cnt_m(n+1,0);
	
	v2ct<ll> dis(n+1,vector<ll>(n+1,1));
	
	for(ll i=1;i<=q;i++){
		string s;
		ll x;
		cin>>x>>s;
		evt.emplace_back(x,(s[0]=='+'));
	}
	
	for(auto [i,c]:evt){
		if(c)
			cnt_p[i]++;
		else
			cnt_m[i]++;
		
		for(ll j=1;j<=n;j++){
			dis[i][j]=max(dis[i][j],cnt_p[j]-cnt_m[i]+1);
			dis[j][i]=max(dis[j][i],cnt_p[i]-cnt_m[j]+1);
		}
	}
	
	v2ct<ll> dp((1<<n)+1,vector<ll>(n+1,INF));
	
	for(ll i=1;i<=n;i++)
		dp[1<<i-1][i]=1;
	
	for(ll st=0;st<=(1<<n)-1;st++){
		for(ll i=1;i<=n;i++){
			if((st>>i-1)&1){
				for(ll j=1;j<=n;j++){
					if((st>>j-1)&1){
						dp[st][i]=min(dp[st][i],dp[st-(1<<i-1)][j]+dis[i][j]);
					}
				}
			}
		}
	}
	
//	for(ll i=1;i<=n;i++)
//		cout<<i<<' '<<dp[1<<i-1][i]<<endl;
	
	for(ll i=1;i<=n;i++)
		ans=min(ans,dp[(1<<n)-1][i]+cnt_p[i]);
	
//	OOO
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

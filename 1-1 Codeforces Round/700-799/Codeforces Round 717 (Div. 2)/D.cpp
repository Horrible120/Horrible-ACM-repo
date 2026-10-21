#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识

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


const ll MAXN = 1e6+1;
ll mob[MAXN+1], pr[MAXN+1];
vector<ll> prm;				//素数序列

void init() {
	bool np[MAXN+1] = {};		//not_prime 数组
	
	
	for (ll i = 1; i <= MAXN; i++)
		mob[i] = 1;				//初始化 莫比乌斯函数 数组
	
	np[1] = 1;
	mob[1] = 1;
	
	for (ll i = 2; i <= MAXN; i++) {
		if (!np[i]) {
			mob[i] = -1;
			pr[i] = i;			//素数在最小素因子是他本身
			prm.emplace_back(i);
		}
		
		for (auto j : prm) {
			
			if (j * i > MAXN) break;
			
			np[i *j] = 1;
			pr[i *j] = j;
			
			if (i % j == 0) {
				mob[i *j] = 0;
				break;
			}
			
			mob[i *j] = -mob[i];
		}
	}
	mob[1] = 0;
}

void solve(){
	ll n,q;
	cin>>n>>q;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<ll> lst(100001,0),ld(n+1,0);
	vector<vector<ll>> dp(n+1,vector<ll>(20,1));
	
	for(ll i=1;i<=n;i++){
		ll tmp=v[i];
		while(tmp>1LL){
			ll tp=pr[tmp];
			ld[i]=max(ld[i],lst[tp]);
			lst[tp]=i;
			while(tmp%tp==0){
				tmp/=tp;
			}
//			cout<<i<<' '<<tmp<<' '<<tp<<endl;
		}
		dp[i][0]=max(dp[i-1][0],ld[i]+1);
	}
	
//	for(ll i=1;i<=n;i++) cout<<i<<' '<<dp[i][0]<<endl;
	
	for(ll i=1;i<20;i++){
		for(ll j=1;j<=n;j++){
			dp[j][i]=dp[j][i-1]>1?dp[dp[j][i-1]-1][i-1]:1;
		}
	}
//	OOO
	while(q--){
		ll l,r;
		cin>>l>>r;
		ll ans=0;
		for(ll i=19;i>=0;i--){
			if(dp[r][i]>l){
				ans+=(1<<i);
				r=dp[r][i]-1;
			}
		}
		cout<<ans+1<<'\n';
	}	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}


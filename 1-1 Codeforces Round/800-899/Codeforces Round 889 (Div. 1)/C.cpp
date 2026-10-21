#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m,ans=0;
	cin>>n>>m;
	
	vector<ll> v(n+1,0);
	vector<vector<ll>> dp(m+1,vector<ll>(m+1,0));
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		ans+=m-v[i]+1;
	}
	
	sort(v.begin()+1,v.end());
	
	for(ll i=1;i<=n;i++){
		if(i>1){
			dp[v[i]][v[i-1]]++;
		}
	}
	
	ll hf=(Mod+1ll)/2;
	
	for(ll i=1;i<=m;i++){
		for(ll j=1;j<i;j++){
			dp[i][j+1]=(dp[i][j+1]+hf*dp[i][j])%Mod;
			if(i<m) dp[i+1][j]=(dp[i+1][j]+hf*dp[i][j])%Mod;
		}
	}
	
	for(ll i=1;i<=m;i++){
		ans=(ans-dp[i][i]*(m-i+1)%Mod+Mod)%Mod;
	}
	
	cout<<ans<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

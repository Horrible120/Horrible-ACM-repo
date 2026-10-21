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
	ll n,k;
	cin>>n>>k;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		v[i]+=v[i-1];
	}
	
	vector<vector<ll>> dp(k+1,vector<ll>(n+1,0));
	
	dp[0][0]=1;
	
	for(ll i=1;i<=n;i++){
		for(ll s=min(v[i]+40,i);s>=max(v[i]-40,0LL);s--){
			for(ll c=k;c>=abs(s-v[i]);c--){
//				cout<<i<<' '<<c<<' '<<s<<endl;
				dp[c][s]=((s<v[i-1]-40||s>v[i-1]+40?0LL:dp[c-abs(s-v[i])][s])+
						  (s==0||s-1<v[i-1]-40||s-1>v[i-1]+40?0LL:dp[c-abs(s-v[i])][s-1]))%Mod;
			}
			for(ll c=abs(s-v[i])-1;c>=0;c--) dp[c][s]=0;
		}
//		
//		cout<<i<<endl;
//		for(ll j=0;j<=k;j++){
//			for(ll l=0;l<=n;l++){
//				cout<<dp[j][l]<<' ';
//			}
//			cout<<endl;
//		}
//		cout<<endl;
	}
	
	ll ans=0;
	
	for(ll i=k;i>=0;i-=2) ans+=dp[i][v[n]];
	
	cout<<ans%Mod<<endl;
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

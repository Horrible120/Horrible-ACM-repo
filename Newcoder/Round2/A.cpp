#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll k,m;
	cin>>k>>m;
	string s;
	cin>>s;
	ll sm=0;
	vector<ll> v(k+1);
	for(ll i=s.size()-1;i>=0;i--)
		v[s.size()-i]=s[i]-'0',sm+=v[s.size()-i];
	for(ll i=s.size()+1;i<=k;i++)
		v[i]=0;
	
	v3ct<ll> dp(k+1,v2ct<ll>(m+2,vector<ll>(2,0)));
	for(ll i=1;i<=m;i++)
		dp[0][i][0]=dp[0][i][1]=0;
	dp[0][0][0]=1;
	dp[0][0][1]=0;
	
	for(ll i=0;i<k;i++){
		for(ll j=0;j<=m;j++){
			dp[i][j][0]%=Mod;
			dp[i][j][1]%=Mod;
			if(v[i+1]==0){
				dp[i+1][j][0]+=dp[i][j][0]+dp[i][j][1];
				dp[i+1][j+1][1]+=dp[i][j][0]+dp[i][j][1];
			}
			else{
				dp[i+1][j+1][0]+=2*dp[i][j][0];
				dp[i+1][j][1]+=2*dp[i][j][1];
			}
		}
	}
	ll ans=dp[k][m][0]+dp[k][m][1];
	if(sm>0) ans=ans*(Mod+1)/2%Mod;
	cout<<ans%Mod<<endl;
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

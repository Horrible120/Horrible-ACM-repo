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

v2ct<ll> dp(160,vector<ll>(160,INF)),bst(160,vector<ll>(160,INF));

void solve(){
	ll x,y,ans=INF;
	cin>>x>>y;
	ll n=0,m=0;
	if(x==0&&y==0){
		cout<<0<<endl;
		return;
	}
	n=__lg(x);
	m=__lg(y);
	ans=bst[n+1][m+1];
	while(n>=0&&m>=0){
		
		if((x>>n)==(y>>m)){
			n--,m--;
//			cout<<n<<' '<<m<<endl;
		}
		else
			break;
//		cout<<"!!!"<<endl;
	}
	n++,m++;
	
	while(n<=150&&m<=150){
		ans=min(ans,dp[n][m]);
		n++,m++;
	}
	
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	dp[0][0]=0;
	for(ll k=1;k<=60;k++){
		for(ll i=150;i>=0;i--)
			for(ll j=150;j>=0;j--){
				if(i>=k) dp[i][j]=min(dp[i][j],dp[i-k][j]+(1ll<<k));
				if(j>=k) dp[i][j]=min(dp[i][j],dp[i][j-k]+(1ll<<k));
			}
	}
	for(ll i=150;i>=0;i--)
		for(ll j=150;j>=0;j--){
			bst[i][j]=min(bst[i+1][j],bst[i][j+1]);
			bst[i][j]=min(bst[i][j],dp[i][j]);
		}
	
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

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

const ll INF = 1e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<array<ll,2>> pnt(n+1,array<ll,2>());
	
	for(ll i=1;i<=n;i++){
		cin>>pnt[i][0];
	}
	
	for(ll i=1;i<=n;i++){
		cin>>pnt[i][1];
	}
	
	vector<vector<ll>> dp(n+1,vector<ll>(k+1,0));
	vector<array<ll,4>> hmax(n+1,array<ll,4>{-INF,-INF,-INF,-INF});
	array<array<ll,2>,4> c{{{1,1},{1,-1},{-1,1},{-1,-1}}},d{{{-1,-1},{1,-1},{-1,1},{1,1}}};
	
	for(ll i=0;i<=n;i++){
		for(ll j=0;j<=min(k,i);j++){
			if(i) dp[i][j]=max(dp[i][j],dp[i-1][j]);
			if(i) for(ll l=0;l<4;l++){
				dp[i][j]=max(dp[i][j],pnt[i][0]*d[l][0]+pnt[i][1]*d[l][1]+hmax[i-j][l]);
			}
			if(i<n) for(ll l=0;l<4;l++){
				hmax[i-j][l]=max(hmax[i-j][l],dp[i][j]+pnt[i+1][0]*c[l][0]+pnt[i+1][1]*c[l][1]);
			}
			
		}
	}
	
//	OOO
	cout<<dp[n][k]<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

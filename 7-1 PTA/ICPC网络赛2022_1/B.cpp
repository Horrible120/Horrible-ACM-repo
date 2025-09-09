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
	ll n;
	cin>>n;
	vector<ll> a(n+1,0),b(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	vector<vector<ll>> dp((1<<n)+1,vector<ll>(n+1,INF));
	
	dp[0][0]=0;
	dp[0][1]=0;
	
	for(ll i=0;i<n;i++){
		for(ll j=0;j<=(1<<n)-1;j++){
			if(__builtin_popcount(j)==i){
				for(ll k=0;k<n;k++){
					if(!(j&(1<<k))){
						ll tmp=j^(1<<k);
						
						for(ll l=0;l<=n;l++){
							dp[tmp][l]=min(dp[tmp][l],dp[j][l]);
						}
//						
//						ll ld=i+1;
//						ll rd=i+1;
//						
//						for(ll l=0;l<n;l++){
//							while(ld+1<=n&&dp[j][ld+1]<=dp[j][i+1]+l*a[k+1]){
//								ld++;
//							}
//							while(rd+1<=n&&rd+1<=ld+l*b[k+1]){
//								rd++;
//								dp[tmp][rd]=min(dp[tmp][rd],dp[j][i+1]+l*a[k+1]);
//							}
//						}
						
						for(ll l=i+2;l<=n;l++){
							for(ll m=i+1;m<=min(n,l);m++){
								dp[tmp][l]=min(dp[tmp][l],max(dp[j][m],dp[j][i+1]+((l-m-1)/b[k+1]+1)*a[k+1]));
							}
						}
						
					}
				}
			}
		}
	}
	
//	for(ll j=0;j<=(1<<n)-1;j++){
//		cout<<">> "<<j<<endl<<"    ";
//		
//		for(ll i=0;i<=n;i++){
//			cout<<dp[j][i]<<' ';
//		}
//		cout<<endl;
//	}
	
//	OOO
	cout<<dp[(1<<n)-1][n];
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

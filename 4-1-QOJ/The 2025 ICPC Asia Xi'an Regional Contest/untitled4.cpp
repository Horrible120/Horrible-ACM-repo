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

ll dp[21][21][21][3][3];

void dfs(ll a,ll b,ll c,ll l,ll r){
	if(dp[a][b][c][l][r]) return;
	
	if(a+b+c==0){
		dp[a][b][c][l][r]=-1;
		return;
	}
	
	if(a+b+c==1){
		if(a) dp[a][b][c][l][r]=((l!=0&&r!=0)?1:-1);
		if(b) dp[a][b][c][l][r]=((l!=1&&r!=1)?1:-1);
		if(c) dp[a][b][c][l][r]=((l!=2&&r!=2)?1:-1);
		return;
	}
	
	if(a){
		dfs(a-1,b,c,0,r);
		dfs(a-1,b,c,l,0);
		if((dp[a-1][b][c][0][r]==1&&l!=0)||(dp[a-1][b][c][l][0]==1&&r!=0)) dp[a][b][c][l][r]=1;
	}
	
	if(b){
		dfs(a,b-1,c,1,r);
		dfs(a,b-1,c,l,1);
		if((dp[a][b-1][c][1][r]==1&&l!=1)||(dp[a][b-1][c][l][1]==1&&r!=1)) dp[a][b][c][l][r]=1;
	}
	
	if(c){
		dfs(a,b,c-1,2,r);
		dfs(a,b,c-1,l,2);
		if((dp[a][b][c-1][2][r]==1&&l!=2)||(dp[a][b][c-1][l][2]==1&&r!=2)) dp[a][b][c][l][r]=1;
	}
	
	if(dp[a][b][c][l][r]==0) dp[a][b][c][l][r]=-1;
	
}

void solve(){
	for(ll i=0;i<=9;i++){
		for(ll j=0;j<=9;j++){
			for(ll k=0;k<=9;k++){
				for(ll l=0;l<=2;l++){
					for(ll r=0;r<=2;r++){
						dfs(i,j,k,l,r);
						cout<<i<<' '<<j<<' '<<k<<' '<<l<<' '<<r<<' '<<dp[i][j][k][l][r]<<endl;
					}
				}
			}
		}
	}
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

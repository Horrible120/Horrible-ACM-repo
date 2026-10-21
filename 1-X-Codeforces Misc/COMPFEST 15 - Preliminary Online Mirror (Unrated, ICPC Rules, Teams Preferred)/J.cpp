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
	ll n,x,y,m=0;
	cin>>n>>x>>y;
	
	vector<ll> v(n+1,0),col(n+1,0),len(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	for(ll i=1;i<=n;i++){
		ll tmp=i;
		while(tmp<=n&&v[tmp]==v[i]) ++tmp;
		col[++m]=v[i];
		len[m]=tmp-i;
		i=tmp-1;
	}
	
	vector<vector<ll>> dp(m+1,vector<ll>(m+1,INF)),f1(m+1,vector<ll>(m+1,INF)),f2(m+1,vector<ll>(m+1,INF));
	
	for(ll i=1;i<=m;i++){
		for(ll j=1;j<i;j++){
			dp[i][j]=0;
		}
	}
	
	for(ll i=1;i<=m;i++){
		dp[i][i]=x;
		f1[i][i]=y*len[i];
		f2[i][i]=2*y*len[i];
	}
	
	for(ll ln=2;ln<=m;ln++){
		for(ll l=1;l<=m-ln+1;l++){
			ll r=l+ln-1;
			if(col[l]==col[r]){
				for(ll j=l;j<r;j++){
					f1[l][r]=min(f1[l][r],f1[l][j]+dp[j+1][r-1]+y*len[r]);
					f2[l][r]=min(f2[l][r],f2[l][j]+dp[j+1][r-1]+2*y*len[r]);
				}
			}
			for(ll j=l;j<=r;j++){
				dp[l][r]=min(dp[l][r],f1[l][j]+x+(j<m?dp[j+1][r]:0ll));
				dp[l][r]=min(dp[l][r],f2[l][j]-2*y*len[j]+x+(j<m?dp[j+1][r]:0ll));
			}
		}
	}
	cout<<dp[1][m]<<endl;
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

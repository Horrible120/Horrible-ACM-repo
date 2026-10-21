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

const ll N=1e5+9;
const ll INF=1e17;
void cmax(ll &a,ll b){
	a=max(a,b);
}
ll tt=1;
ll n,d;
ll js(ll a,ll b,ll t,ll j,ll k){
	bool pd=false;
	if(b>=3-k&&a>=3-j)pd=true;
	ll res=0;
	if(t>0){
		a-=t;
		if(a<0)return -INF;
	}
	if(t<0){
		b+=t;
		if(b<0)return -INF;
		res+=2*d*(-t);
	}
	res+=min(a,b)*2*d;
	a-=min(a,b);
	if(pd)res+=a*d;
	return res;
}
ll a[N],b[N];
ll dp[N][4];
void solve(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	dp[0][0]=0;
	dp[0][1]=dp[0][2]=dp[0][3]=-INF;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=3;j++){
			for(int k=0;k<=3;k++){
				cmax(dp[i][k],dp[i-1][j]+js(a[i],b[i],k-j,j,k)+k);
			}
		}
	}
	ll ans=-INF;
	for(int i=0;i<4;i++)cmax(ans,dp[n][i]);
	cout<<ans;
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

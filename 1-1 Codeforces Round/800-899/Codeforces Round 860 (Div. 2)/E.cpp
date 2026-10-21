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
	vector<ll> v(n+1,0),dp1(n+1,0),dp2(n+1,0),ans(n+1,0),dp3(n+1,0);
	ll mx1=0;
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	for(ll i=n;i>=2;i--){
		if(i+v[i]>n){
			dp1[i]=0;
			dp2[i]=0;
			dp3[i]=mx1+1;
		}else if(i+v[i]==n){
			dp1[i]=1;
			dp2[i]=1;
			dp3[i]=mx1+1;
		}else{
			dp1[i]=dp1[i+v[i]+1]+1;
			dp2[i]=dp2[i+v[i]+1];
			dp3[i]=max(mx1+1,dp3[i+v[i]+1]+1);
		}
		
		if(dp2[i]==1){
			if(dp1[i]==v[i-1]){
				ans[i]=0;
			}else{
				ans[i]=1;
			}
		}else{
			if(dp3[i]>=v[i-1]){
				ans[i]=1;
			}else{
				ans[i]=2;
			}
		}
		
		if(dp2[i]==1) mx1=max(mx1,dp1[i]);
	}
	
//	OOO
	for(ll i=2;i<=n;i++){
		cout<<ans[i]<<' ';
	}
	cout<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

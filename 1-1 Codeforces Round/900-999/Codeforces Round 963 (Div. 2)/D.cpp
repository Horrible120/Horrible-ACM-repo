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

void solve(){
	ll n,k,m;
	cin>>n>>k;
	m=(n-1)%k+1;
	vector<ll> v(n+1,0),dp(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	ll l=0,r=1e9;
	while(l<r){
		ll mid=l+r+1>>1;
//		dp.assign(n+1,0);
		for(ll i=0;i<=m;i++)
			dp[i]=0;
		for(ll i=1;i<=n;i++){
			ll tmp=(i-1)%k+1;
			if(v[i]>=mid)
				dp[tmp]=dp[tmp-1]+1;
			else
				dp[tmp]=max(dp[tmp-1],dp[tmp]);
		}
		if(dp[m]>=m/2+1)
			l=mid;
		else
			r=mid-1;
	}
//	OOO
	cout<<l<<endl;
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

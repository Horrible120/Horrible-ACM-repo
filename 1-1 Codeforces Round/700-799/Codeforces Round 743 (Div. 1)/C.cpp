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
	ll n;
	cin>>n;
	vector<ll> a(1,0);
	for(ll i=1;i<=n;i++){
		ll val;
		cin>>val;
		if(val!=a[a.size()-1])
			a.emplace_back(val);
	}

	ll m=a.size()-1;
	vector<ll> nxt(m+2,m+1),lst(n+1,m+1);
	for(ll i=m;i>=1;i--){
		nxt[i]=lst[a[i]];
		lst[a[i]]=i;
	}

	vector<vector<ll>> dp(m+2,vector<ll>(m+2));
	for(ll len=2;len<=m;len++){
		for(ll l=1;l+len-1<=m;l++){
			ll r=l+len-1;
			dp[l][r]=dp[l+1][r];
			for(ll k=nxt[l];k<=r;k=nxt[k])
				dp[l][r]=max(dp[l][r],dp[l+1][k-1]+dp[k][r]+1);
		}
	}

	cout<<m-1-dp[1][m]<<'\n';
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

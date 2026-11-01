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
	ll n,k,len;
	string s;
	cin >> n >> k >> len >> s;
	vector<ll> a(n+1);
	for (ll i=1;i<=n;i++)
		a[i]=(s[i-1]>='a'&&s[i-1]<='z');

	vector<pair<ll,ll>> dp(n+1);
	auto check=[&](ll cost)->pair<ll,ll>{
		fill(dp.begin(),dp.end(),make_pair(INF,INF));
		dp[0]={0,0};
		for (ll i=0;i<n;i++) {
			dp[i+1]=min(dp[i+1],make_pair(dp[i].first+a[i+1],dp[i].second));
			ll pos=min(n,i+len);
			dp[pos]=min(dp[pos],make_pair(dp[i].first+cost,dp[i].second+1));
		}
		return dp[n];
	};

	auto calc=[&]()->ll{
		ll l=0,r=n;
		while (l<r) {
			ll mid=(l+r)/2;
			if (check(mid).second<=k)
				r=mid;
			else
				l=mid+1;
		}
		return check(l).first-l*k;
	};

	ll ans=calc();
	for (ll i=1;i<=n;i++)
		a[i]^=1;
	ans=min(ans,calc());
	cout << ans << '\n';
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

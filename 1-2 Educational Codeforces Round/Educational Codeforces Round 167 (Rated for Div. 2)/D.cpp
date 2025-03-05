#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<pair<ll,ll>> v(n+1);
	for(ll i=1;i<=n;i++)
		cin>>v[i].first;
	for(ll i=1;i<=n;i++)
		cin>>v[i].second;
	auto cmp=[](const pair<ll,ll> &a,const pair<ll,ll> &b){
		return a.first<b.first;
	};
	sort(v.begin()+1,v.end(),cmp);
	vector<ll> dp(1e6+1);
	dp[0]=0;
	ll pos=1,mn=INF;
	for(ll i=1;i<=1e6;i++){
		while(pos<=n&&i>=v[pos].first){
			mn=min(mn,v[pos].first-v[pos].second);
			pos++;
		}
		if(i>=mn)
			dp[i]=dp[i-mn]+2;
	}
	ll ans=0;
	for(ll i=1;i<=m;i++){
		ll x;
		cin>>x;
		if(x>1e6){
			ll tmp=(x-1e6+mn)/mn;
			x-=tmp*mn;
			ans+=2*tmp;
		}
		ans+=dp[x];
	}
//	H_test(ans);
	println("{}",ans);
//	cout<<ans<<endl;
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

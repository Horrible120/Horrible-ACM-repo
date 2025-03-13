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
	map<ll,ll> ans;
	ll sum=0;
	
	for(ll i=1;i<=n;i++)
		cin>>v[i].first;
	for(ll i=1;i<=n;i++)
		cin>>v[i].second;
	
	for(ll i=1;i<=n;i++){
		auto &[x,R]=v[i];
		ll l=x-R,r=x+R;
		for(ll j=l;j<=r;j++){
			sum-=ans[j];
			ans[j]=max(ans[j],(ll)sqrtl(R*R-abs(j-x)*abs(j-x)+0.0000001)*2+1);
			sum+=ans[j];
		}
	}
//	OOO
	cout<<sum<<endl;
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

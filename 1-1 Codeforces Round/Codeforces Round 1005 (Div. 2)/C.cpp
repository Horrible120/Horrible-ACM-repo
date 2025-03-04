#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<ll> a(n+1),pre1(n+2),pre2(n+2);
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=n;i++){
		if(a[i]>0) pre1[i]=pre1[i-1]+a[i];
		else pre1[i]=pre1[i-1];
	}
	for(ll i=n;i>=1;i--){
		if(a[i]<0) pre2[i]=pre2[i+1]-a[i];
		else pre2[i]=pre2[i+1];
	}
	for(ll i=1;i<=n+1;i++)
		ans=max(ans,pre1[i-1]+pre2[i]);
//	OOO
	cout<<ans<<endl;
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

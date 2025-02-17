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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,cnt=0,minh=1e9,maxh=0;
	cin>>n;
	vector<ll> a(n+1),b(n+1);
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=n;i++) cin>>b[i];
	for(ll i=1;i<=n;i++){
		if(a[i]<b[i]) cnt++,maxh=max(maxh,b[i]-a[i]);
		else minh=min(minh,a[i]-b[i]);
	}
	if(cnt>1) cout<<"NO"<<endl;
	else{
		if(maxh>minh) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	
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

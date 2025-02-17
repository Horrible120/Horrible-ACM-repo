#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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
	ll n,l,r,ans1=0,ans2=0;
	cin>>n>>l>>r;
	vector<ll> v(n+1),a(n+1),b(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	for(ll i=1;i<=r;i++) a[i]=v[i];
	for(ll i=l;i<=n;i++) b[i-l+1]=v[i];
	
	sort(a.begin()+1,a.begin()+r+1);
	sort(b.begin()+1,b.begin()+(n-l+1)+1);
	
	for(ll i=1;i<=r-l+1;i++){
		ans1+=a[i];
		ans2+=b[i];
	}
	
//	OOO
	cout<<min(ans1,ans2)<<endl;
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

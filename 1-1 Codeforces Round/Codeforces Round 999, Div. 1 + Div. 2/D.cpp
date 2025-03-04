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
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1),b(n+1);
	multiset<ll,greater<ll>> aa,bb;
	ll suma=0,sumb=0;
	for(ll i=1;i<=n;i++) cin>>a[i],aa.insert(a[i]),suma+=a[i];
	for(ll i=1;i<=m;i++) cin>>b[i],bb.insert(b[i]),sumb+=b[i];
	
	if(suma!=sumb){
		CN
		return;
	}
	
	while(aa.size()&&bb.size()){
		ll fb=*bb.begin(),fa=*aa.begin();
		if(fb==fa){
			bb.erase(bb.begin());
			aa.erase(aa.begin());
		}
		else if(fb>fa){
			bb.erase(bb.begin());
			bb.insert(fb/2);
			bb.insert((fb+1)/2);
		}
		else
			break;
	}
	if(aa.size()||bb.size()) CN
	else CY
	
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

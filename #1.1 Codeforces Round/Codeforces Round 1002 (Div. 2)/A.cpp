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
	ll n,cnta=0,cntb=0;
	cin>>n;
	vector<ll> a(n+1),b(n+1);
	map<ll,ll> A,B;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		if(!A[a[i]]) cnta++,A[a[i]]=1;
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
		if(!B[b[i]]) cntb++,B[b[i]]=1;
	}
	if((cnta>2||cntb>2)||(cnta+cntb>=4)) CY
	else CN
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

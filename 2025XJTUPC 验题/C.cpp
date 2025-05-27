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
	ll n;
	cin>>n;
	vector<long double> a(1<<n,0),b(1<<n,0),ans(n+1,0);
	
	for(ll i=0;i<(1<<n);i++){
		cin>>a[i]>>b[i];
		for(ll g=0;g<n;g++){
			if((i>>g)&1){
				ans[g]+=a[i]*a[i]+b[i]*b[i];
			}
		}
	}
	for(ll i=0;i<n;i++)
		cout<<(long double)1-ans[i]<<' '<<ans[i]<<endl;
	
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

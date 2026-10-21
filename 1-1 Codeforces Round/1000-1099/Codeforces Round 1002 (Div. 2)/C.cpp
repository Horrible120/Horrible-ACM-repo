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
	ll n;
	cin>>n;
	v2ct<ll> a(n+1,vector<ll>(n+1));
	vector<ll> len(n+1);
 	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			cin>>a[i][j];
	for(ll i=1;i<=n;i++){
		ll pos=n;
		while(pos>0)
			if(a[i][pos--]==1)
				len[i]++;
			else
				break;
//		cout<<i<<' '<<len[i]<<endl;
	}
	sort(len.begin()+1,len.end());
	ll ans=1;
	for(ll i=1;i<=n;i++){
		if(len[i]>=ans) ans++;
	}
//	OOO
	cout<<min(ans,n)<<endl;
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

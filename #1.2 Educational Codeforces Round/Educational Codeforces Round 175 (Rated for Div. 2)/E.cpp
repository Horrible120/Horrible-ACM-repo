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
	ll n,ans=0;
	cin>>n;
	string s;
	cin>>s;
	vector<ll> v(n+1,0);
	oset<pair<ll,ll>> st;
	for(ll i=1;i<=n;i++)
		v[i]=v[i-1]+(s[i-1]=='1'?-3:1),st.insert(make_pair(v[i],i));
	for(ll i=0;i<n;i++){
		ans+=st.order_of_key(make_pair(v[i]-1,INF))-st.order_of_key(make_pair(v[i]-1,0))+(n-i)-st.order_of_key(make_pair(v[i]+2,0));
		st.erase(make_pair(v[i+1],i+1));
	}
	cout<<ans<<endl;
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

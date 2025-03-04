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
unordered_map<ll,ll> mp;

void solve(){
	ll n;
	cin>>n;
	if(mp[n*(n+1)/2]){
		cout<<-1<<endl;
		return;
	}
	for(ll i=1;i<=n;i++){
		if(mp[i*(i+1)/2]){
			cout<<i+1<<' '<<i<<' ';
			i++;
		}
		else
			cout<<i<<' ';
	}
	cout<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	for(ll i=1;i<=5e5;i++) mp[i*i]=1;
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

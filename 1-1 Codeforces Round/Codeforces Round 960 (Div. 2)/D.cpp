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
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	ll ans=n,lst1=0,lst2=0;
	for(ll i=1;i<=n;i++){
		if(v[i]==0){
			lst1=0;
			lst2=0;
			ans--;
		}
		else if(v[i]<=2){
			if(i%2==0&&lst1!=0){
				ans--;
				lst1=lst2=0;
				continue;
			}
			if(i%2==1&&lst2!=0){
				ans--;
				lst1=lst2=0;
				continue;
			}
			if(i%2==1) lst1=1;
			else lst2=1;
		}
		else if(v[i]>4){
			lst1=lst2=0;
		}
	}
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

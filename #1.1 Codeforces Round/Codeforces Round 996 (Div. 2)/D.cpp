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
	ll n,k,need;
	cin>>n>>k>>need;
	k*=2;
	need*=2;
	vector<ll> pos(n+1);
	for(ll i=1;i<=n;i++)
		cin>>pos[i],pos[i]*=2;
	ll tick=pos[1],po=k;
	ll ans=need-po+tick;
	for(ll i=2;i<=n;i++){
		if(pos[i]+tick<=po-k) continue;
		else if(pos[i]+tick<=po) po=pos[i]+tick+k;
		else if(pos[i]-tick<=po) po+=k;
		else {
			ll tmp=(pos[i]-tick-po)/2;
			tick+=tmp;
			po+=tmp+k;
		}
		if(po>=need){
			if(po-k<=need) ans=min(ans,tick);
			break;
		}
		ans=need-po+tick;	
	}
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

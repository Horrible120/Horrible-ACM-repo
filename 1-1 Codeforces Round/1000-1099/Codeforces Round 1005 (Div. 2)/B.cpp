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
	map<ll,ll> cnt;
	for(ll i=1;i<=n;i++) cin>>v[i],cnt[v[i]]++;
	ll ansl=1,ansr=0;
	for(ll i=1;i<=n;i++){
		ll tmp=i;
		if(cnt[v[i]]>1) continue;
		while(i+1<=n&&cnt[v[i+1]]==1) i++;
		if(i-tmp>ansr-ansl){
			ansl=tmp;
			ansr=i;
		}
	}
//	OOO
	if(ansr==0) cout<<0<<endl;
	else cout<<ansl<<' '<<ansr<<endl;
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

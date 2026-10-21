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
	ll n,x,ans=1;
	cin>>n>>x;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	map<ll,ll> mp;
	mp[x]=1;
	for(ll i=1;i<=n;i++){
		vector<ll> tmp;
		for(auto [val,bi]:mp){
			if(bi&&val%v[i]==0)
				tmp.emplace_back(val/v[i]);
		}
			
		for(auto it:tmp)
			mp[it]=1;
		if(mp[1]){
			ans++;
			mp.clear();
			mp[x]=1;
			if(x%v[i]==0)
				mp[x/v[i]]=1;
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

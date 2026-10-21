#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	
	ll ans=n;
	
	vector<ll> v(n+1,0);
	vector<vector<ll>> que(n*2+1);
	vector<set<ll,greater<ll>>> cnt(n*2+2);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		cnt[v[i]].insert(i);
		que[v[i]].emplace_back(i);
	}
	
	for(ll i=1;i<=2*n;i++){
		for(auto p:que[i]){
			if(cnt[i-1].size()&&cnt[i-1].lower_bound(p)!=cnt[i-1].end()){
				cnt[i-1].erase(cnt[i-1].lower_bound(p));
				ans--;
			}else if(cnt[i+1].size()&&cnt[i+1].lower_bound(p)!=cnt[i+1].end()){
				cnt[i+1].erase(cnt[i+1].lower_bound(p));
				ans--;
			}
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

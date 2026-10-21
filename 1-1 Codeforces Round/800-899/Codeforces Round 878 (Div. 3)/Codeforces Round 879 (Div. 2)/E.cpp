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
	vector<ll> v(n+1,0);
	vector<set<ll>> lc(n+1);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<ll> vis(15*n+1,0);
	
	for(ll i=1;i<=n;i++){
		lc[i].insert(v[i]);
		if(v[i]<=n*15) vis[v[i]]=1;
		while(lc[i-1].size()){
			ll ttmp=*lc[i-1].begin();
			ll tmp=ttmp*v[i]/__gcd(ttmp,v[i]);
			lc[i-1].erase(lc[i-1].begin());
			if(tmp<=15*n){
				vis[tmp]=1;
				lc[i].insert(tmp);
			}
		}
	}
	
	for(ll i=1;i<=n*15;i++){
		if(!vis[i]){
//			OOO
			cout<<i<<endl;
			return;
		}
	}
	
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

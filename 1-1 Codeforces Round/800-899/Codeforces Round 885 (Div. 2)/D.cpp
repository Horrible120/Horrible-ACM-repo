#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll s,k;
	cin>>s>>k;
	
	vector<ll> vis(10,0);
	
	ll ans=0;
	
	while(k){
		ll g=s%10;
		if(vis[g]) break;
		if(g&1LL||g==0){
			ans=max(ans,s*k);
		}else{
			ll x=(5*k-s+20LL)/40LL;
			x=max(x,0LL);
			x=min(x,k/4LL);
			ans=max(ans,(s+20LL*x)*(k-4LL*x));
		}
		vis[g]=1;
		s+=g;
		k--;
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
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

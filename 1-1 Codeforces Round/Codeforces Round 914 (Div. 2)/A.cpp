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
	ll a,b;
	cin>>a>>b;
	ll xk,yk,xq,yq;
	cin>>xk>>yk>>xq>>yq;
	
	set<pair<ll,ll>> ans;
	
	ll dx[9]={0,a,a,-a,-a,b,b,-b,-b};
	ll dy[9]={0,b,-b,b,-b,a,-a,a,-a};
	
	for(ll i=1;i<=8;i++){
		for(ll j=1;j<=8;j++){
			if(xk+dx[i]==xq+dx[j]&&yk+dy[i]==yq+dy[j]){
				ans.insert(make_pair(xk+dx[i],yk+dy[i]));
			}
		}
	}
	
//	OOO
	cout<<ans.size()<<endl;
	
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

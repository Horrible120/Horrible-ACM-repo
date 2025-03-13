#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull; 
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;
ll ans[1000002];

void solve(){
	ll n;
	cin>>n;
//	OOO
	cout<<ans[n]<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	ans[2]=1;
	ans[3]=2;
	for(ll i=4;i<=1e6;i++)
		ans[i]=(((ans[i-1]-ans[i-2]-1)*i+(i-2)+ans[i-1]+1)%Mod+Mod)%Mod;
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

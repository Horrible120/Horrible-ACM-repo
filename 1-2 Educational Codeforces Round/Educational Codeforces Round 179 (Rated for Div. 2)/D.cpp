#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	
	vector<ll> room(m+1,0);
	vector<array<ll,7>> ans(n+1);
	
	for(ll i=1;i<=m;i++){
		cin>>room[i];
	}
	
//	OOO
	
	sort(room.begin()+1,room.end());
	
	for(ll i=2;i<=n;i+=2){
		for(ll j=1;j<=6;j+=2){
			ans[i][j]=room[i/2];
			ans[i-1][j]=room[m-i/2+1];
		}
		for(ll j=2;j<=6;j+=2){
			ans[i][j]=room[m-i/2+1];
			ans[i-1][j]=room[i/2];
		}
	}
	
	if(n&1){
		
		for(ll j=1;j<=6;j+=2)
			ans[n][j]=room[n/2+1];
		for(ll j=2;j<=6;j+=2)
			ans[n][j]=room[m-(n/2+1)+1];
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=6;j++)
			cout<<ans[i][j]<<' ';
		cout<<'\n';
	}
	cout.flush();
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

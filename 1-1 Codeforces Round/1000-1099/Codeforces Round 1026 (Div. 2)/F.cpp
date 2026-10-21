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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),ans(n+1,0);
	
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	ll mx=v[1];
	
	for(ll i=1;i<=n;i++){
		if(v[i]<=mx){
			ans[i]=max(ans[i-1],mx%v[i]+v[i]%mx);
		}
		else{
			if(mx>=v[i]/2+1){
				ans[i]=v[i];
			}
			else{
				for(ll j=1;j<=i;j++){
					ans[i]=max(ans[i],v[j]%v[i]+v[i]%v[j]);
				}
			}
			mx=v[i];
		}
	}
	
	for(ll i=1;i<=n;i++)
		cout<<ans[i]<<" \n"[i==n];
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

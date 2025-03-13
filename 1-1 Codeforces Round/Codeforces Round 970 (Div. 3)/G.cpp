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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> v(n+1);
	ll gg=0;
	for(ll i=1;i<=n;i++) cin>>v[i],gg=__gcd(gg,v[i]);
	
//	OOO
	
	if(n==1){
		if(k>v[1])
			cout<<k<<endl;
		else
			cout<<k-1<<endl;
		return;
	}
	
	ll l=0,r=INF;
	while(l<r){
		ll mid=(l+r)/2;
		ll tmp=mid+1-min(n,mid/gg+1);
		if(tmp>=k) r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;
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

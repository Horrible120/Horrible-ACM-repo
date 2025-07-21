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
	ll n,m;
	cin>>n>>m;
	vector<ll> b(n+1),w(m+1);
	for(ll i=1;i<=n;i++)
		cin>>b[i];
	for(ll i=1;i<=m;i++)
		cin>>w[i];
	sort(b.begin()+1,b.end(),greater<ll>());
	sort(w.begin()+1,w.end(),greater<ll>());
	ll ans=0;
	ll tmp=0;
	ll l=1;
//	if(lower_bound(b.begin()+1)
	for(ll i=0;i<=m;i++){
		while(l<=n&&b[l]>0) tmp+=b[l++];
		if(i>n) break;
		while(l<=i) tmp+=b[l++];
		tmp+=w[i];
		ans=max(ans,tmp);
	}
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

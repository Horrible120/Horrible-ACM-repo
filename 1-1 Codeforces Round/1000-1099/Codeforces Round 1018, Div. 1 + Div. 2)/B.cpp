#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

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
	ll n,k,ans=0;
	cin>>n>>k;
	vector<ll> l(n+1,0),r(n+1,0),p(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>l[i];
	for(ll i=1;i<=n;i++)
		cin>>r[i];
	for(ll i=1;i<=n;i++){
		p[i]=l[i]+r[i]-max(l[i],r[i]);
		ans+=max(l[i],r[i]);
	}
	sort(p.begin()+1,p.end(),greater<ll>());
	for(ll i=1;i<=k-1;i++)
		ans+=p[i];
//	OOO
	cout<<ans+1<<endl;
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

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
	ll n,k,cnt=0;
	cin>>n>>k;
	vector<ll> col(n+1,0),val(n+1,0);
	
	for(ll i=1;i<=n;i+=k){
		cnt++;
		ll l=i,r=min(l+k-1,n);
		ll mid=(l+r+1)/2;
		for(ll j=l;j<=mid;j++)
			val[j]=mid-j+l;
		for(ll j=mid+1;j<=r;j++)
			val[j]=r-j+mid+1;
		for(ll j=l;j<=r;j++)
			col[j]=cnt;
	}
	
//	OOO
	for(ll i=1;i<=n;i++)
		cout<<val[i]<<" \n"[i==n];
	cout<<cnt<<endl;
	for(ll i=1;i<=n;i++)
		cout<<col[i]<<" \n"[i==n];
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

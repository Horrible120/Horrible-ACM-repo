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
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+2,0),b(m+2,0);
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=m;i++)
		cin>>b[i];
	vector<ll> pre(m+2,INF),suf(m+2,-INF);
	
	pre[0]=0;
	suf[m+1]=n+1;
	ll l=1;
	for(ll i=1;i<=n&&l<m;i++)
		if(a[i]>=b[l]){
			pre[l]=i;
			l++;
		}
	ll r=m;
	for(ll i=n;i>=1&&r>0;i--)
		if(a[i]>=b[r]){
			suf[r]=i;
			r--;
		}
	
	ll ans=INF;
	
	for(ll i=0;i<=m-1;i++)
		if(pre[i]<suf[i+2])
			ans=min(ans,b[i+1]);
	
	for(ll i=0;i<=m;i++)
		if(pre[i]<suf[i+1])
			ans=0;
	
//	OOO
	if(ans==INF)
		cout<<-1<<endl;
	else
		cout<<ans<<endl;
	
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

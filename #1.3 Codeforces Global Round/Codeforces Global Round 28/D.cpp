#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,st,ln=0;
	cin>>n>>m;
	vector<ll> a(n+1),b(m+1),x(m+1);
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=m;i++)
		cin>>b[i];
	st=a[1];
	
	sort(a.begin()+1,a.end(),greater<ll>());
	sort(b.begin()+1,b.end(),greater<ll>());
	
	for(ll i=1;i<=n;i++) if(a[i]<=st) ln++;
	ll cur=0;
//	OOO
	for(ll i=1;i<=m;i++){
		while(cur<n&&a[cur+1]>=b[i]) cur++;
		x[i]=cur+1;
		if(b[i]<=st) x[i]=1;
//		cout<<x[i]<<" \n"[i==m];
	}
	sort(x.begin()+1,x.end());
//	OOO
	for(ll i=1;i<=m;i++){
		ll ans=0;
		for(ll j=i;j<=m;j+=i){
			ans+=x[j];
		}
		cout<<ans<<" \n"[i==m];
	}
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

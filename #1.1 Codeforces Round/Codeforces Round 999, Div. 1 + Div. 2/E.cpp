#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,k,ans=0,sum=0;
	cin>>n>>m>>k;
	vector<ll> a(n+1),b(m+1);
	v2ct<ll> dif(n+1,vector<ll>(m+1,0));
	
	for(ll i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	for(ll i=1;i<=m;i++) cin>>b[i];
	
	multiset<ll,greater<ll>> s;
	
	for(ll i=1;i<(1<<m);i++){
		ll tmp=(1<<30)-1,cnt=__builtin_popcount(i);
		
		for(ll j=0;j<m;j++)
			if((i>>j)&1)
				tmp&=b[j+1];
		
		for(ll j=1;j<=n;j++)
			dif[j][cnt]=max(dif[j][cnt],a[j]-(a[j]&tmp));
	}
	
//	for(ll i=1;i<=n;i++)
//		dif[i][0]=a[i];
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			s.insert(dif[i][j]-dif[i][j-1]);
	
	while(k--){
		sum-=*s.begin();
		s.erase(s.begin());
	}
	
//	OOO
	cout<<sum<<endl;
	
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

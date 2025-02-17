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
	ll n,m,dmg=0;
	ll x=1,y=1,k=0;
	cin>>n>>m;
	vector<ll> a(n+1),b(m+1),v(n+1);
	for(ll i=1;i<=n;i++) cin>>a[i],k+=(a[i]>1);
	for(ll i=1;i<=m;i++) cin>>b[i];
	sort(a.begin()+1,a.end());
	sort(b.begin()+1,b.end());
	if(a[1]==1) ++k;
	
	while(y<=m){
		while(x<=n||y<=m){
			if(x<=n&&a[x]<=dmg+1)
				x++,dmg++;
			else if(y<=m&&b[y]<=dmg)
				y++,dmg++;
			else break;
		}
		if(y<=m)
			if(b[y]<=dmg+k){
				k-=b[y]-dmg;
				b[y]=dmg;
				y++,dmg++;
			}
			else break;
	}
	
	if(y>m) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
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

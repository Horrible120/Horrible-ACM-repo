#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll p1,t1,p2,t2,h,s,n;
	cin>>p1>>t1>>p2>>t2>>h>>s;
	
	n=h+max(p1,p2);
	
	vector<ll> f(n+1,INF),g(n+1,INF);
	
	g[0]=0;
	f[0]=0;
	
	for(ll i=1;i<=h;i++){
		ll dmg;
		dmg=(p1-s)*i+(p2-s)*(i*t1/t2)+s*(i*t1>=t2?1:0);
		if(dmg<=n) f[dmg]=min(f[dmg],t1*i);
		dmg=(p2-s)*i+(p1-s)*(i*t2/t1)+s*(i*t2>=t1?1:0);
		if(dmg<=n) f[dmg]=min(f[dmg],t2*i);
	}
	ll ans=INF;
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<i;j++){
			g[i]=min(g[i],g[j]+f[i-j]);
		}
//		cout<<i<<' '<<f[i]<<' '<<g[i]<<endl;
		if(i>=h) ans=min(ans,g[i]);
	}
//	OOO
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

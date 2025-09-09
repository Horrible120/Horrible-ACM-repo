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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

void solve(){
	ll n,m,sum=0;
	cin>>n>>m;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		sum+=v[i];
	}
	
	sum%=m;
	
	ll x1,x2,y,d;
	
	ll a=n*(n+1)/2%m;
	
	exgcd(n,m,d,x1,y);
	exgcd(a,m,d,x2,y);
	
	x1=((x1%m)+m)%m;
	x2=((x2%m)+m)%m;
	
//	cout<<a<<' '<<x1<<' '<<x2<<endl;
	
	ll g1=__gcd(n,m);
	ll g2=__gcd(a,m);
	
	if(g1==0&&g2==0){
		cout<<sum%m<<endl;
		cout<<0<<' '<<0<<endl;
		return;
	}
	
	ll gg=__gcd(g1,g2);
	
	ll ans=sum%gg;
	ll op=(sum-ans)/gg;
	
	ll x3,y3;
	
	exgcd(g1,g2,d,x3,y3);
	
//	cout<<g1<<' '<<g2<<endl;
//	cout<<x3<<' '<<y3<<endl;
	
	ll anss=((-x3*x1%m*op)%m+m)%m;
	ll ansd=((-y3*x2%m*op)%m+m)%m;
	
	cout<<ans<<endl<<anss<<' '<<ansd<<endl;
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

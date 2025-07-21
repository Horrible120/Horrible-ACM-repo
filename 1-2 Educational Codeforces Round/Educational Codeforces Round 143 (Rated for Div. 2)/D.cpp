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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	ll n,fans=1;
	cin>>n;
	vector<ll> w(n+1,0),ans(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>w[i];
	}
	
	ll tn=n/3;
	for(ll i=1;i<=tn;i++){
		fans=fans*i%Mod;
	}
	for(ll i=1;i<=tn/2;i++){
		fans=fans*inv(i)%Mod*inv(i)%Mod;
	}
	
	for(ll i=1;i<=tn;i++){
		ll min_val=min(w[i*3],min(w[i*3-1],w[i*3-2]));
		fans=fans*((w[i*3]==min_val)+(w[i*3-1]==min_val)+(w[i*3-2]==min_val))%Mod;
	}
//	OOO
	cout<<fans<<endl;
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

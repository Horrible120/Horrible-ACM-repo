#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k,m;
	cin>>n>>k>>m;
	
	ll ans=0;
	

	k%=m;
	
	
	auto qpow=[&](ll x,ll p){
		ll ret=1,y=(x%m+m)%m;
		while(p){
			if(p%2) ret=ret*y%m; 
			p>>=1ll;
			y=y*y%m;
		}
		return ret;
	};
	
	if(k==1||n==1){
		ans=1;
	}else if(k%2){
		ans=(qpow(k,n)-qpow(k-1,n)+qpow(-1,n)-qpow(-1,n)*__gcd(k,n-2)%m)%m+m;
	}else{
		ans=((qpow(k,n)-qpow(k-2,n)+qpow(-2,n))*((m+1)/2LL)%m-qpow(-1,n)*qpow(2,n-1)%m*__gcd(k/2,n-2)%m)%m+m;
	}
	
//	OOO
	cout<<ans%m<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

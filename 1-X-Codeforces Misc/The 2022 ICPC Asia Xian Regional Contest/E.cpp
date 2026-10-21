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
	ll ld,rd;
	cin>>ld>>rd;
	auto calc=[&](ll x){
		if(x==0) return 1LL;
		ll ret=0;
		while(x>0){
			ret+=x%3+1;
			x/=3;
		}
		return ret;
	};
	auto sol=[&](auto &&self,ll l,ll r)->ll{
		if(l>r) return 0LL; 
		if(r<3) return r+1;
		ll nl=0,nr=0,ret=0;
		nr=(r-3)/3;
		nl=(l+3)/3;
		ret=self(self,nl,nr)+3;
		for(ll i=l;i<=min(r,l+5);i++){
			ret=max(ret,calc(i));
		}
		for(ll i=r;i>=max(l,r-5);i--){
			ret=max(ret,calc(i));
		}
		return ret;
	};
	
//	OOO
	cout<<sol(sol,ld,rd)<<'\n';
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

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
	ll n,m;
	cin>>n>>m;
	
	ll ans=0,ak=1;
	
	for(ll k=2;k<=m;k++){
		
		ll cnt=0;
		
		for(ll i=0;i<k/__gcd(k,n);i++){
			
			ll str=(i*n+1+k-1)/k;
			ll end=(i+1)*n/k;
			
			ll st=i*n/(k-1)+1;
			
			ll ld=max(str,st);
			
			if(ld<=end){
				cnt+=((ld*k-1)%n+1+(end*k-1)%n+1)*(end-ld+1)/2ll;
			}
			
		}
		if(cnt>ans){
			ans=cnt;
			ak=k;
		}
	}
	
	cout<<ak<<endl;
	
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

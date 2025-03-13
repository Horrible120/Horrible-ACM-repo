#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll a1,a2,x=0,y=0;
	ll ask1=0b101010101010101010101010101010,
		ask2=0b010101010101010101010101010101;
	cout<<ask1<<endl;
	cin>>a1;
	cout<<ask2<<endl;
	cin>>a2;
	
	a1-=2*ask1;
	a2-=2*ask2;
	
	for(ll i=1;i<=29;i+=2){
		ll f1=(a2>>i)&1,f2=(a2>>i+1)&1;
		if(f2==1)
			x+=1<<i,y+=1<<i;
		else if(f1==1)
			x+=1<<i;
	}
	for(ll i=0;i<=29;i+=2){
		ll f1=(a1>>i)&1,f2=(a1>>i+1)&1;
		if(f2==1)
			x+=1<<i,y+=1<<i;
		else if(f1==1)
			x+=1<<i;
	}
	cout<<'!'<<endl;
	ll m;
	cin>>m;
	cout<<(x|m)+(y|m)<<endl;
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

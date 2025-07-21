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
	ll n;
	cin>>n;
	if(n>=6){
		cout<<4<<endl;
		for(ll i=1;i<=n;i++)
			cout<<i%4+1<<' ';
		cout<<endl;
	}
	else{
		if(n==1){
			cout<<1<<endl;
			cout<<1<<endl;
		}
		if(n==2){
			cout<<2<<endl;
			cout<<"1 2"<<endl;
		}
		if(n==3){
			cout<<2<<endl;
			cout<<"1 2 2"<<endl;
		}
		if(n==4){
			cout<<3<<endl;
			cout<<"1 2 2 3"<<endl;
		}
		if(n==5){
			cout<<3<<endl;
			cout<<"1 2 2 3 1"<<endl;
		}
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

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

void solve(){
	ll x1,x2,x3,x4,y1,y2,y3,y4;
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
	
	if(x1>x2||y1>y2){
		swap(x1,x2);
		swap(y1,y2);
	}
	if(x3>x4||y3>y4){
		swap(x3,x4);
		swap(y3,y4);
	}
	
	if(abs(x1-x2)==abs(x3-x4)){
		ll disx=abs(x1-x3);
		ll disy=abs(y1-y3);
		cout<<max(disx,disy)*2<<'\n';
	}else{
		ll dis=INF;
		dis=min(dis,max(abs(x1-x3),abs(y1-y3)));
		dis=min(dis,max(abs(x2-x3),abs(y2-y3)));
		dis=min(dis,max(abs(x1-x4),abs(y1-y4)));
		dis=min(dis,max(abs(x2-x4),abs(y2-y4)));
		cout<<dis*2+1<<'\n';
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

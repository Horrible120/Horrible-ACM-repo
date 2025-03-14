#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	ll f=-1,c=-1;
	for(ll i=63;i>=0;i--)
		if((n>>i)&1)
			if(f==-1) f=i;
			else if(c==-1) c=i;
			else break;
//	cout<<"!!!"<<f<<' '<<c<<endl;
	if(c!=-1&&m==(1ll<<c+1)-1){
		cout<<1<<endl<<n<<' '<<m<<endl;
		return;
	}
	if(c!=-1&&m<(1ll<<c+1)-1){
		cout<<2<<endl<<n<<' '<<(1ll<<c+1)-1<<' '<<m<<endl;
		return;
	}
	for(ll i=63;i>=0;i--)
		if((m>>i)&1){
			if((n>>i)&1)
				cout<<1<<endl<<n<<' '<<m<<endl;
			else
				cout<<-1<<endl;
			return;
		}
}
// 101011111101000100100101110000011100000000011010110101110001
// 001111111111111111111111111111111111111111111111111111111111
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

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

map<ll,ll> f;

void solve(){
	ll x;
	cin>>x;
//	OOO
	if(f[x])
		cout<<-1<<endl;
	else{
		for(ll i=1;i<=32;i++){
			if(((x>>i)&1)==1&&((x>>i-1)&1)==0){
				cout<<(1<<i)+(1<<i-1)<<endl;
				return;
			}
			else if(((x>>i)&1)==0&&((x>>i-1)&1)==1){
				cout<<(1<<i)+(1<<i-1)<<endl;
				return;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	for(ll i=1;i<=40;i++)
		f[1<<i]=1,f[(1<<i)-1]=1;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

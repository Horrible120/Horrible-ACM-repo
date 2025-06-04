#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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

class H_basis{
public:
	ll dgt;
	vector<ll> d;
	H_basis(ll _dgt){
		dgt=_dgt;
		d.assign(dgt+1,0);
	}
	
	void insert(ll val){
		for(ll i=dgt;i>=0;i--){
			if(!(val&(1ll<<i))){
				continue;
			}
			if(!d[i]){
				d[i]=val;
				break;
			}
			else{
				val^=d[i];
			}
		}
	}
	
	ll get_max(){
		ll res=0;
		for(ll i=dgt;i>=0;i--){
			if((res^d[i])>res){
				res^=d[i];
			}
		}
		return res;
	}
	
};

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	
	H_basis bas(60);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		bas.insert(v[i]);
	}
	
//	OOO
	cout<<bas.get_max()<<endl;
	
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

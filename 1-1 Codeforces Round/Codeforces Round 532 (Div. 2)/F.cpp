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
	ll dg;
	ll zeroflag;
	vector<ll> d,t;
	
	H_basis(ll _dg){
		dg=_dg;
		d.assign(dg,0);
		t.assign(dg,0);
	}
	
	bool insert(ll val,ll ti){
		for(ll i=dg-1;i>=0;i--){
			if(val>>i&1){
				if(d[i]){
					if(t[i]<ti){
						swap(t[i],ti);
						swap(d[i],val);
					}
					val^=d[i];
				}else{
					d[i]=val;
					t[i]=ti;
					return true;
				}
			}
		}
		zeroflag=true;
		return false;
	}
	
	ll get_max(ll l){
		ll res=0;
		for(ll i=dg-1;i>=0;i--){
			if(!(res>>i&1)&&t[i]>=l){
				res^=d[i];
			}
		}
		return res;
	}
	
};

void solve(){
	ll n,q;
	cin>>n;
	
	vector<H_basis> preb(n+1,20);
	
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		preb[i]=preb[i-1];
		preb[i].insert(x,i);
	}
	
	cin>>q;
	for(ll i=1;i<=q;i++){
		ll l,r;
		cin>>l>>r;
//		OOO
		cout<<preb[r].get_max(l)<<'\n';
	}
	
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

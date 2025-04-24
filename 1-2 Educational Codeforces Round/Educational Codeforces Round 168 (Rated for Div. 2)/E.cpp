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

class H_Fenwick_Tree{
public:
	ll n;
	vector<ll> val;
	H_Fenwick_Tree(ll _n){
		n=_n;
		val.assign(n+1,0);
	}
	
	ll query_ps(ll x){
		ll res=0;
		while(x>0){
			res+=val[x];
			x-=x&-x;
		}
		return res;
	}
	
	ll query(ll l,ll r){
		return query_ps(r)-query_ps(l-1);
	}
	
	void modify_add(ll pos,ll k){
		while(pos<=n){
			val[pos]+=k;
			pos+=pos&-pos;
		}
	}
	
};

void solve(){
	ll n,q;
	cin>>n>>q;
	vector<ll> v(n+1,0),ans(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	H_Fenwick_Tree fwk(n);
	
	for(ll i=1;i<=n;i++){
		ll l=0,r=n;
		while(l<r){
			ll mid=(l+r)/2;
			if(fwk.query_ps(mid)>=mid*v[i])
				l=mid+1;
			else
				r=mid;
		}
		ans[i]=l;
		fwk.modify_add(l,1);
	}
	
	while(q--){
		ll k,x;
		cin>>x>>k;
		if(k>=ans[x])
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
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

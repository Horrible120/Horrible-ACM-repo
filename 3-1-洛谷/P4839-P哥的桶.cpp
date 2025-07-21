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

const ll dg=30;
class H_base{
public:
	vector<ll> d;
	ll zero_flag;
	H_base(){
		d=vector<ll>(dg+1);
		zero_flag=0;
	}
	
	bool insert(ll val){
		for(ll i=dg;i>=0;i--){
			if(val>>i&1){
				if(!d[i]){
					d[i]=val;
					return true;
				}else{
					val^=d[i];
				}
			}
		}
		return false;
	}
	
	void merge(const H_base &bas){
		for(ll i=0;i<=dg;i++){
			if(bas.d[i]){
				insert(bas.d[i]);
			}
		}
	}
	
	ll get_max(){
		ll res=0;
		for(ll i=dg;i>=0;i--){
			if((res^d[i])>res){
				res^=d[i];
			}
		}
		return res;
	}
};

class H_sgm{
public:
	ll n;
	vector<H_base> tr;
	
	H_sgm(ll _n){
		n=_n;
		tr.assign(n*4+5,H_base());
	}
	
	void modify(ll pos,ll key){
		modify(1,1,n,pos,key);
	}
	
	ll query(ll s,ll t){
		H_base res=H_base();
		query(1,1,n,s,t,res);
		return res.get_max();
	}
	
private:
	void modify(ll u,ll l,ll r,ll pos,ll key){
		tr[u].insert(key);
		if(l==r){
			return;
		}
		ll mid=l+r>>1;
		if(pos<=mid){
			modify(u*2,l,mid,pos,key);
		}else{
			modify(u*2+1,mid+1,r,pos,key);
		}
	}
	
	void query(ll u,ll l,ll r,ll s,ll t,H_base &bas){
		if(l>=s&&r<=t){
			bas.merge(tr[u]);
			return;
		}
		ll mid=l+r>>1;
		if(mid>=s){
			query(u*2,l,mid,s,t,bas);
		}
		if(mid+1<=t){
			query(u*2+1,mid+1,r,s,t,bas);
		}
	}
	
};

void solve(){
	ll n,m;
	cin>>n>>m;
	
	H_sgm sgm(n);
	
	for(ll i=1;i<=n;i++){
		ll op;
		cin>>op;
		if(op==1){
			ll k,x;
			cin>>k>>x;
			sgm.modify(k,x);
		}else{
			ll l,r;
			cin>>l>>r;
			cout<<sgm.query(l,r)<<endl;
		}
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

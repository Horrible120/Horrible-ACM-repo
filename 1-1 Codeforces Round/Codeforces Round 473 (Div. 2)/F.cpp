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
	ll dg,zero_flag;
	vector<ll> d,p;
	
	H_basis(ll _dg){
		dg=_dg;
		zero_flag=0;
		d.assign(dg+1,0);
	}
	
	void print(){
		for(ll i=0;i<=dg;i++)
			cout<<d[i]<<endl;
	}
	
	bool insert(ll val){
		for(ll i=dg;i>=0;i--){
			if((val>>i)&1){
				if(!d[i]){
					d[i]=val;
					return true;
				}
				else
					val^=d[i];
			}
		}
		zero_flag=true;
		return false;
	}
	
	bool check(ll val){
		for(ll i=dg;i>=0;i--){
			if((val>>i)&1){
				if(!d[i]){
					return false;
				}
				val^=d[i];
			}
		}
		return true;
	}
	
	ll get_max(){
		ll res=0;
		for(ll i=dg;i>=0;i--){
			if((res^d[i])>res) res^=d[i];
		}
		return res;
	}
	
	ll get_min(){
		if(zero_flag) return 0;
		for(ll i=0;i<=dg;i++)
			if(d[i]) return d[i];
	}
	
	void rebuild(){
		for(ll i=0;i<=dg;i++){
			for(ll j=i-1;j>=0;j--){
				if((d[i]>>j)&1){
					d[i]^=d[j];
				}
			}
		}
		
		p.resize(0);
		
		for(ll i=0;i<=dg;i++){
			if(d[i]) p.emplace_back(d[i]); 
		}
	}
	
	ll kth_min(ll k){
		if(zero_flag) k--;
		if(k>=(1ll<<(ll)p.size())) return -1;
		ll res=0;
		for(ll i=0;i<=dg;i++){
			if((k>>i)&1) res^=d[i];
		}
		return res;
	}
	
	void merge(const H_basis &bas){
		for(ll i=0;i<=dg;i++){
			if(bas.d[i]) insert(bas.d[i]);
		}
		zero_flag|=bas.zero_flag;
	}
	
	H_basis friend operator +(const H_basis &a,const H_basis &b){
		H_basis res=a;
		res.merge(b);
		return res;
	}
	
};

void solve(){
	ll n,q;
	cin>>n>>q;
	vector<H_basis> bas(n+1,H_basis(20));
	vector<ll> zero(n+1,0);
	
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		bas[i]=bas[i-1];
		zero[i]=zero[i-1];
		zero[i]+=(!bas[i].insert(x));
	}
	
//	for(ll i=1;i<=n;i++){
//		cout<<zero[i]<<' ';
//	}
//	cout<<endl; 
	
	while(q--){
		ll l,x;
		cin>>l>>x;
		if(!bas[l].check(x)){
			cout<<0<<endl;
		}
		else{
			ll tmp=zero[l];
			ll c=2,ans=1;
			while(tmp){
				if(tmp&1){
					ans=ans*c%Mod;
				}
				tmp>>=1;
				c=c*c%Mod;
			}
//			OOO
			cout<<ans<<endl;
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

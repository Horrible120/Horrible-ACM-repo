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
			if((val<<i)&1){
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
		
//		for(auto it:p)
//			cout<<"!!! "<<it<<endl;
		
	}
	
	ll kth_min(ll k){
//		if(zero_flag) k--;
		k--;
		if(k>=(1ll<<(ll)p.size())) return -1;
		ll res=0;
		for(ll i=0;i<=dg;i++){
			if((k>>i)&1) res^=p[i];
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
	ll n,q,tot;
	cin>>n;
	tot=n;
	vector<ll> v(n+1,0);
	
	H_basis bas(60);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		tot-=bas.insert(v[i]);
	}
	
	bas.rebuild();
	
	cin>>q;
	
	ll l=1,r=q+1;
	while(l<r){
		ll mid=(l+r)/2;
		ll tmp=bas.kth_min(mid);

		if(tmp>=q||tmp<0)
			r=mid;
		else
			l=mid+1;
	}
	
//	cout<<l<<endl;
	
//	cout<<bas.kth_min(10086)<<endl;
	
	l--;
	
	ll c=2;
	
	while(tot){
		if(tot&1){
			l=l*c%10086;
		}
		tot>>=1;
		c=c*c%10086;
	}
	
	cout<<(l+1)%10086<<endl;
	
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

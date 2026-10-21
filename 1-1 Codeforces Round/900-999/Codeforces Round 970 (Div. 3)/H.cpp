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

class H_fwk{
public:
	ll n;
	vector<ll> val;
	
	H_fwk(ll _n){
		n=_n;
		val.assign(n+1,0);
	}
	
	ll query_pre(ll pos){
		ll res=0;
		while(pos>0){
			res+=val[pos];
			pos-=pos&-pos;
		}
		return res;
	}
	
	ll query(ll l,ll r){
		return query_pre(r)-query_pre(l-1);
	}
	
	void add(ll pos){
		while(pos<=n){
			val[pos]++;
			pos+=pos&-pos;
		}
	}
	
};

void solve(){
	ll n,q;
	cin>>n>>q;
	ll m=n/2+1;
	H_fwk fwk(n+1);
	vector<ll> v(n+1,0),ans(n+2,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		fwk.add(v[i]+1);
	}
	for(ll k=1;k<=n;k++){
		ll l=0,r=k-1;
		while(l<r){
			ll mid=(l+r)>>1,cnt=0;
			for(ll i=1;i<=n+1;i+=k)
				cnt+=fwk.query(i,min(i+mid,n+1));
			if(cnt>=m) r=mid;
			else l=mid+1;
		}
		ans[k]=l;
	}
	while(q--){
		ll x;
		cin>>x;
//		OOO
		cout<<ans[x]<<' ';
	}
	cout<<endl;
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

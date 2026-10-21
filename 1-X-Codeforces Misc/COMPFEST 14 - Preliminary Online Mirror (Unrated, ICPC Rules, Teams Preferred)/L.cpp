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

class H_fwk{
public:
	ll n;
	vector<ll> v;
	
	H_fwk(ll _n){
		n=_n;
		v.assign(n+1,0);
	}
	
	ll query(ll x){
		ll res=0;
		while(x>0){
			res+=v[x];
			x^=(x&-x);
		}
		return res;
	}
	
	void modify(ll pos,ll k){
		while(pos<=n){
			v[pos]+=k;
			pos+=(pos&-pos);
		}
	}
};

void solve(){
	ll n,flag=1;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		v[i]+=v[i-1];
		if(v[i]<0) flag=0; 
	}
	
	if(v[n]<*max_element(v.begin()+1,v.end())) flag=0;
	
	if(!flag){
		cout<<-1<<endl;
		return;
	}
	
	H_fwk fwk(n);
	
	auto v2=v;
	sort(v2.begin()+1,v2.end());
	v2.erase(unique(v2.begin()+1,v2.end()),v2.end());
	for(ll i=1;i<=n;i++) v[i]=lower_bound(v2.begin()+1,v2.end(),v[i])-v2.begin();
	
//	for(ll i=1;i<=n;i++) cout<<v[i]<<' ';
//	cout<<endl;
	
	ll ans=0;
	
	for(ll i=1;i<=n;i++){
		fwk.modify(v[i],1);
		ans+=fwk.query(v[i]);
	}
	
//	OOO
	cout<<n*(n+1)/2-ans<<endl;
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

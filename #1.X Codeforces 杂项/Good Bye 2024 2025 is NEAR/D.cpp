#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 998244353;

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
    ll d,x,y;
    exgcd(a,Mod,d,x,y);
    return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	ll n,q,ans=1;
	cin>>n>>q;
	vector<ll> a(n+1),b(n+1);
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=n;i++) cin>>b[i];
	
	oset<pair<ll,ll>,less<pair<ll,ll>>> A,B;
//	oset<pair<ll,ll>,greater<pair<ll,ll>>> ;
	
	for(ll i=1;i<=n;i++){
		A.insert(make_pair(a[i],i));
		B.insert(make_pair(b[i],i));
	}
	
	function<ll(ll)> Min=[&](ll x){
		return min((*A.find_by_order(x)).first,(*B.find_by_order(x)).first);
	};
	
	for(ll i=1;i<=n;i++)
		ans=ans*Min(i-1)%Mod;
//	OOO
	cout<<ans<<' ';
	
	ll o,x;
	for(ll i=1;i<=q;i++){
		cin>>o>>x;
		ll tmp=0;
		if(o==1){
			ll stg=A.order_of_key(make_pair(a[x]+1,-1))-1;
			ans=ans*inv(Min(stg))%Mod;
			
			A.erase(A.find(make_pair(a[x],x)));
			a[x]++;
			A.insert(make_pair(a[x],x));
			
			ans=ans*Min(stg)%Mod;
		}
		else{
			ll stg=B.order_of_key(make_pair(b[x]+1,-1))-1;
			ans=ans*inv(Min(stg))%Mod;
			
			B.erase(B.find(make_pair(b[x],x)));
			b[x]++;
			B.insert(make_pair(b[x],x));
			
			ans=ans*Min(stg)%Mod;
		}
		
		cout<<ans<<' ';
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

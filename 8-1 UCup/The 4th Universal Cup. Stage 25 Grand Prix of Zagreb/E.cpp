#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q;
	cin>>n>>q;
	
	vector<ll> val(n+1,0),pref(n+1,0),ans(q+1,0);
	vector<pair<ll,ll>> vx(q+1);
	
	for(ll i=1;i<=n;i++){
		cin>>val[i];
		pref[i]=pref[i-1]+val[i];
	}
	
	for(ll i=1;i<=q;i++){
		cin>>vx[i].first;
		vx[i].second=i;
	}
	
	sort(vx.begin()+1,vx.end());
	
	for(ll i=1;i<=n;i++){
		pref[i]+=i*vx[1].first;
	}
	
	for(ll i=q;i>=1;i--){
		vx[i].first-=vx[1].first;
	}
	
	for(ll i=1;i<=q;i++){
		ll x=vx[i].first;
		
		ll max_val=x+pref[1],min_val=x+pref[1];
		
		{
			ll l=1,r=n;
			while(l<r){
				ll mid=l+r>>1;
			}
			
			while()
		}
		
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

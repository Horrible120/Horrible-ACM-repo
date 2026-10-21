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

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	v[0]=-1;
	
	vector<ll> tmp(n+1,0);
	
	sort(v.begin()+1,v.end(),greater<ll>());
	
	ll ans=0;
	
	for(ll i=1;i<=n;i++){
		if(ans>=v[i]) break;
		if(v[i]==v[i-1]) continue;
		multiset<ll,greater<ll>> s;
		for(ll j=1;j<=n;j++){
			if(j==i) continue;
			ll a=v[j]%v[i];
			s.insert(a);
			auto it=s.upper_bound((v[i]-a)%v[i]);
			if(it!=s.end()) ans=max(ans,(*it+a)%v[i]);
		}
		ans=max(ans,((*s.begin())+(*next(s.begin())))%v[i]);
		
	}
	
//	OOO
	cout<<ans<<endl;
	
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

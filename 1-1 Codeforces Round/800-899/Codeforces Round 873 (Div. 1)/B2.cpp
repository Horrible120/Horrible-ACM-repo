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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),rnk(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		rnk[i]=i;
	}
	
	sort(rnk.begin()+1,rnk.end(),[&](const ll a,const ll b){return v[a]<v[b];});
	
	set<ll> s[2];
	
	for(ll i=0;i<=n+1;i++) s[0].insert(i);
	
	s[1].emplace(n+1);
	
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans+=(i-1)*(n-i+1);
	}
	
	for(ll i=1;i<=n;i++){
		ll b=rnk[i];
		ll a=*(--s[0].lower_bound(b));
		ll c=*(s[0].upper_bound(b));
		ll d=*(s[1].upper_bound(c));
		if(c!=n+1) ans-=(b-a)*(d-c);
		s[0].erase(b);
		s[1].insert(b);
	}
	
	cout<<ans<<endl;
	
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

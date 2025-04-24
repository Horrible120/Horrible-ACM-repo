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
v2ct<int> fct(500010,vector<int>());

void init(){
	ll n=500000;
	for(ll i=1;i<=n;i++)
		for(ll j=i;j<=n;j+=i)
			fct[j].emplace_back(i);
}

void solve(){
	ll n,ans=0,cnt=0;
	cin>>n;
	vector<ll> v(n+1),x(n+1),y(n+1);
	v2ct<int> cntx(n+1,vector<int>()),cnty(n+1,vector<int>());
	
	for(ll i=1;i<=n;i++){
		ll g;
		cin>>v[i];
		g=__gcd(i,v[i]);
		x[i]=i/g;
		y[i]=v[i]/g;
		
		cntx[x[i]].emplace_back(i);
		cnty[y[i]].emplace_back(i);
		
		if(x[i]==1) cnt++;
	}
	
	vector<ll> c(n+1,0);
	for(ll i=1;i<=n;i++){
		for(auto it:cntx[i])
			for(auto f:fct[y[it]])
				c[f]++;
		
		for(ll yy=i;yy<=n;yy+=i)
			for(auto k:cnty[yy])
				ans+=c[x[k]];
		
		for(auto it:cntx[i])
			for(auto f:fct[y[it]])
				c[f]--;
	}
//	OOO
	cout<<(ans-cnt)/2<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}

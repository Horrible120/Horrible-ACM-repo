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

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

ll fct[200001],iv[200001];

void init(){
	ll n=200000;
	fct[0]=1;
	for(ll i=1;i<=n;i++){
		fct[i]=fct[i-1]*i%Mod;
	}
	iv[n]=inv(fct[n]);
	for(ll i=n-1;i>=0;i--){
		iv[i]=iv[i+1]*(i+1)%Mod;
	}
}

ll cal(ll n,ll m){
	return fct[n]*iv[m]%Mod*iv[n-m]%Mod;
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	if(k&1){
		cout<<1<<endl;
		return;
	}
	
	ll ans=0;
	
	vector<ll> vis(n+1,0),sum(n+1,0);
	
	auto dfs=[&](this auto &&self,ll u)->void{
		vis[u]=true;
		sum[u]=1;
		for(auto v:eg[u]) if(!vis[v]){
			self(v);
			sum[u]+=sum[v];
			if(sum[v]>=k/2&&n-sum[v]>=k/2){
				ans=(ans+cal(sum[v],k/2)*cal(n-sum[v],k/2))%Mod;
			}
		}
	};
	
	dfs(1);
	
//	for(ll i=1;i<=n;i++) cout<<i<<' '<<sum[i]<<endl;
	
	ans=(ans*inv(cal(n,k))+1LL)%Mod;
	
	cout<<ans<<endl;
	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
		
	init();
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}

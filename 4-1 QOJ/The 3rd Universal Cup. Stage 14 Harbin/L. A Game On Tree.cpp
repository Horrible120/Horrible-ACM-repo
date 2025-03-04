#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

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
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<ll> eg[n+1];
	for(ll i=1;i<=n-1;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> vsiz(n+1),ssiz(n+1);
	function<void(ll,ll)> DFS1=[&](ll u,ll fa){
		vsiz[u]=1;
		vector<ll> son;
		for(auto v:eg[u]){
			if(v==fa) continue;
			DFS1(v,u);
			son.emplace_back(v);
			vsiz[u]+=vsiz[v];
		}
		ssiz[u]=vsiz[u]*vsiz[u];
		for(auto v:son)
			ssiz[u]+=ssiz[v];
	};
	DFS1(1,0);
	function<void(ll,ll)> DFS2=[&](ll u,ll fa){
//		cout<<u<<' '<<ssiz[u]<<' '<<vsiz[u]<<endl;
		for(auto v:eg[u]){
			if(v==fa) continue;
			DFS2(v,u);
			ans=(ans+(vsiz[v]*(n-vsiz[v])%Mod)*(vsiz[v]*(n-vsiz[v])%Mod))%Mod;
			ans=(ans+2*((ssiz[v]-vsiz[v]*vsiz[v])%Mod)*((n-vsiz[v])*(n-vsiz[v])%Mod))%Mod;
			ans=(ans+(ssiz[v]%Mod)*((ssiz[u]-vsiz[u]*vsiz[u]-ssiz[v])%Mod))%Mod;
		}
	};
	DFS2(1,0);
//	OOO
//	cout<<ans<<endl;
	cout<<(ans*inv(((n*(n-1)/2)%Mod)*((n*(n-1)/2)%Mod)%Mod))%Mod<<endl;
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

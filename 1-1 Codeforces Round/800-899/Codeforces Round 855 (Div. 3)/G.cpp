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
const ull mask=rnd();

ull f(ull x){
	x^=mask;
	x^=x<<13;
	x^=x>>7;
	x^=x<<17;
	x^=mask;
	return x;
}

void solve(){
	ll n;
	cin>>n;
	vector<vector<ll>> eg(n+1);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ull> hs(n+1,0),vis(n+1,0),dp(n+1,0);
	
	auto DFS=[&](auto &&self,ll u)->void{
		hs[u]=1;
		vis[u]=1;
		ull xr=0,cnt=0;
		vector<ll> tmp;
		for(auto v:eg[u]){
			if(!vis[v]){
				tmp.emplace_back(v);
				self(self,v);
				hs[u]+=f(hs[v]);
				xr^=hs[v];
				cnt++;
			}
		}
		
		if(cnt&1){
			for(auto v:tmp){
				if(hs[v]==xr){
					dp[u]=dp[v];
					return;
				}
			}
		}else{
			dp[u]=(xr==0);
		}
		
	};
	
	DFS(DFS,1);
	if(dp[1]){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	
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

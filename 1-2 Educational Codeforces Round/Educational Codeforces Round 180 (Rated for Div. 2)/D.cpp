#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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

void solve(){
	ll n;
	cin>>n;
	
	vector<ll> idx(n+1,0);
	
	vector<vector<ll>> eg(n+1);
	
	for(ll i=1;i<=n-1;i++){
		ll u,v;
		cin>>u>>v;
		
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
		
		idx[u]++;
		idx[v]++;
		
	}
	
	ll rt=0;
	
	for(ll i=1;i<=n;i++){
		if(idx[i]==2){
			rt=i;
			break;
		}
	}
	
	if(!rt){
		cout<<"NO"<<endl;
		return;
	}
	
	vector<ll> vis(n+1,0),tp(n+1,0);
	vector<pair<ll,ll>> ans;
	
	ll a=eg[rt][0],b=eg[rt][1];
	tp[a]=1;
	tp[b]=0;
	
	ans.emplace_back(a,rt);
	ans.emplace_back(rt,b);
	
	auto DFS=[&](auto &&self,ll u)->void{
		for(auto v:eg[u]){
			if(!vis[v]){
				vis[v]=1;
				if(u!=rt){
					tp[v]=1-tp[u];
					if(tp[u]==1)
						ans.emplace_back(make_pair(u,v));
					else
						ans.emplace_back((make_pair(v,u)));
				}
				self(self,v);
			}
		}
	};
	
	vis[rt]=1;
	DFS(DFS,rt);
	
	cout<<"YES"<<endl;
	for(auto [u,v]:ans)
		cout<<u<<' '<<v<<endl;
	
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

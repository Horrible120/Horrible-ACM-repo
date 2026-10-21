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

void solve(){
	ll n,q;
	cin>>n>>q;
	
	v2ct<ll> eg(n+1);
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> fa(n+1,0),dep(n+1,0),son(n+1,0);
	
	auto DFS=[&](auto &&self,ll u)->void{
		for(auto v:eg[u]){
			if(!fa[v]){
				fa[v]=u;
				dep[v]=dep[u]+1;
				self(self,v);
				son[u]++;
			}
		}
	};
	
	fa[1]=1;
	dep[1]=1;
	DFS(DFS,1);
	
	for(ll i=1;i<=q;i++){
		ll u,coin,ans=0;
		cin>>u>>coin;
		
		vector<ll> tmp;
		ll tu=fa[u];
		while(tu!=1){
			ans+=eg[tu].size()*2-1;
			tmp.emplace_back(eg[tu].size()*2-1);
			tu=fa[fa[tu]];
		}
		
		ans+=dep[u]/2;
		
		ll m=min((ll)tmp.size(),coin);
		
		sort(tmp.begin(),tmp.end(),greater<ll>());
		
//		cout<<m<<endl;
		
		for(ll j=0;j<m;j++)
			ans-=tmp[j]-1;
		
//		OOO
		cout<<ans<<endl;
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

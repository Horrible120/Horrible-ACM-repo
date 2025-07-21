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
	ll n,q,ans=0;
	cin>>n>>q;
	vector<map<ll,ll>> eg(n+1);
	vector<ll> fa(n+1,0),col(n+1,0),sons(n+1,0);
	vector<ll> sum_fa(n+1,0);
	vector<map<ll,ll>> sum_son(n+1);
	
	for(ll i=1;i<=n;i++){
		cin>>col[i];
	}
	
	for(ll i=1;i<n;i++){
		ll u,v,c;
		cin>>u>>v>>c;
		eg[u][v]=c;
		eg[v][u]=c;
	}
	
	auto DFS=[&](auto &&self,ll u)->void{
		for(auto [v,c]:eg[u]){
			if(v!=fa[u]){
				fa[v]=u;
				sum_fa[v]=(col[v]!=col[u])?c:0;
				ans+=sum_fa[v];
				sum_son[u][col[v]]+=c;
				self(self,v);
			}
		}
	};
	
	fa[1]=0;
	DFS(DFS,1);
	
	for(ll i=1;i<=q;i++){
		ll u,x;
		cin>>u>>x;
		
		if(u!=1){
			ll c=eg[u][fa[u]];
			ans-=(col[fa[u]]!=col[u])?c:0;
			ans+=(col[fa[u]]!=x)?c:0;
			sum_son[fa[u]][col[u]]-=c;
			sum_son[fa[u]][x]+=c;
		}
		ans+=sum_son[u][col[u]];
		ans-=sum_son[u][x];
		
//		OOO
		cout<<ans<<endl;
		
		col[u]=x;
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

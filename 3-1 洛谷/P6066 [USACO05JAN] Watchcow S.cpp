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
	ll n,m;
	cin>>n>>m;
	vector<unordered_multiset<ll>> eg(n+1);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].insert(v);
		eg[v].insert(u);
	}
	
	vector<ll> ans;
	
	auto DFS=[&](auto &&self,ll u)->void{
		while(eg[u].size()){
			ll v=*eg[u].begin();
			eg[u].erase(eg[u].find(v));
			self(self,v);
		}
		ans.emplace_back(u);
	};
	
	DFS(DFS,1);
	
	reverse(ans.begin(),ans.end());
	for(auto it:ans)
		cout<<it<<endl;
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

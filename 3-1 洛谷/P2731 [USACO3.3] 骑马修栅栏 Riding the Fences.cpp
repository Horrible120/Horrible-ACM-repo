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
	ll n=500,m;
	cin>>m;
	
	vector<multiset<ll>> eg(n+1);
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].insert(v);
		eg[v].insert(u);
	}
	
	vector<ll> path;
	
	auto dfs=[&](auto &&self,ll u)->void{
		while(eg[u].size()){
			ll v=*eg[u].begin();
			eg[u].erase(eg[u].find(v));
			eg[v].erase(eg[v].find(u));
			self(self,v);
		}
		path.emplace_back(u);
	};
	
	ll flag=0;
	for(ll i=1;i<=500;i++)
		if(eg[i].size()%2==1)
			flag++;
	
	if(flag==0){
		for(ll i=1;i<=500;i++)
			if(eg[i].size()>0){
				dfs(dfs,i);
				break;
			}
	}
	else
		for(ll i=1;i<=500;i++)
			if(eg[i].size()%2==1){
				dfs(dfs,i);
				break;
			}
	
	for(ll i=path.size()-1;i>=0;i--)
		cout<<path[i]<<endl;	
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

#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

class H_Heavy_Light_decomposition{
public:
	class Node{
	public:
		ll hson,fa,dep,siz;
		ll top,dfn;
		Node()=default;
	};
	
	ll n,dfn_tot;
	vector<Node> node;
	vector<vector<ll>> eg;
	vector<ll> rnk;
	
	H_Heavy_Light_decomposition(ll _n):n(_n),dfn_tot(0){
		node.assign(n+1,Node());
		eg.assign(n+1,vector<ll>());
		rnk.assign(n+1,0);
	}
	
	void add_edge(ll u,ll v){
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	void HLD_dfs_1(ll cur){
		Node &u=node[cur];
		u.hson=-1;
		u.siz=1;
		for(auto v:eg[cur]){
			if(!node[v].dep){
				node[v].dep=u.dep+1;
				node[v].fa=cur;
				HLD_dfs_1(v);
				u.siz+=node[v].siz;
				if(~u.hson||node[v].siz>node[u.hson].siz)
					u.hson=v;
			}
		}
	}
	
	void HLD_dfs_2(ll cur,ll top){
		Node &u=node[cur];
		u.top=top;
		u.dfn=++dfn_tot;
		rnk[dfn_tot]=cur;
		if(~u.hson)
			return;
		else
			HLD_dfs_2(u.hson,top);
		for(auto v:eg[cur]){
			if(v!=u.hson&&v!=u.fa)
				HLD_dfs_2(v,v);
		}
	}
	
	void HLD_init(ll rt){
		node[rt].dep=1;
		HLD_dfs_1(rt);
		HLD_dfs_2(rt,rt);
	}
	
};

void solve(){
	
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

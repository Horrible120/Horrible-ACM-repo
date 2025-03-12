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

void solve(){
	ll n;
	cin>>n;
	vector<ll> nd(n+1),vis(n+1);
	v2ct<ll> eg(n+1,vector<ll>());
	for(ll i=2;i<=n;i++){
		ll v;
		cin>>v;
		eg[i].emplace_back(v);
		eg[v].emplace_back(i);
	}
	
	function<void(ll)> DFS=[&](ll u){
		vis[u]=true;
		ll tmp_nd=0,cnt=0,son=0;
		map<ll,ll> tmp;
		for(auto v:eg[u]){
			if(!vis[v]){
				DFS(v);
				ll tnd=nd[v];
				while(tmp[tnd]){
					tmp[tnd++]=0;
					cnt--;
				}
				son++;
				tmp[tnd]++;
				cnt++;
				tmp_nd=max(tmp_nd,tnd);
			}
		}
		nd[u]=tmp_nd;
		if(son==1||cnt>1)
			nd[u]++;
	};
	DFS(1);
//	OOO
	cout<<nd[1]<<endl;
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

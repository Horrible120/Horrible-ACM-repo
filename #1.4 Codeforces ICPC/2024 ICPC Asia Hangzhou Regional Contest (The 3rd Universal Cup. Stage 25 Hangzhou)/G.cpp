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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> eg[n+1],nxt(n+1),is_ring(n+1),fst_ring(n+1),vis(n+1);
	for(ll i=1;i<=n;i++){
		ll v;
		cin>>v;
		eg[i].emplace_back(v);
		eg[v].emplace_back(i);
		nxt[i]=v;
	}
	
//	function<void(ll,ll)> DFS1=[&](ll x){
//		if(vis[x]) return;
//		vis[x]=1;
//		
//	}
	
	for(ll i=1;i<=n;i++){
		if(is_ring[i]!=0) continue;
		ll cur=i;
		while(1){
			if(is_ring[cur]!=0||vis[cur]>=2) break;
			vis[cur]++;
			cur=nxt[cur];
		}
		cur=i;
		while(1){
			if(is_ring[cur]!=0) break;
			if(vis[cur]==1) is_ring[cur]=-1;
			else is_ring[cur]=1;
		}
	}
	
	for(ll i=1;i<=n;i++) cout<<is_ring[i]<<' ';
	cout<<endl;
	
	
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

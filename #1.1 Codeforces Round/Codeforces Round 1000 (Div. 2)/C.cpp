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
	ll n;
	cin>>n;
	vector<ll> eg[n+1];
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> dp0(n+1),dp1(n+1),dp2(n+1),vis(n+1);	//只删了他一个 只删了一个但不是他 删了两个
	
	function<void(ll)> DFS=[&](ll x){
		if(vis[x]) return;
		vis[x]=1;
		dp0[x]=eg[x].size();
		vector<ll> tmp;
		for(auto it:eg[x]){
			if(!vis[it]){
				DFS(it);
				
				tmp.emplace_back(max(dp0[it],dp1[it]));
				
				dp1[x]=max(dp1[x],dp0[it]);
				dp1[x]=max(dp1[x],dp1[it]);
				
				dp2[x]=max(dp2[x],dp0[x]+dp0[it]-2);
				dp2[x]=max(dp2[x],dp0[x]+dp1[it]-1);
				dp2[x]=max(dp2[x],dp2[it]);
			}
		}
		if(tmp.size()>1){
			sort(tmp.begin(),tmp.end(),greater<ll>());
			dp2[x]=max(dp2[x],tmp[0]+tmp[1]-1);
		}
	};
	
	DFS(1);
//	OOO
	cout<<dp2[1]<<endl;
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

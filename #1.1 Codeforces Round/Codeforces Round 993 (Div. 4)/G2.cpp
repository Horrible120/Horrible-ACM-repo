#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> r(n+1),book(n+1),ring(n+1),dvis(n+1),subt(n+1);
	vector<vector<ll>> son(n+1);
	
	function<void(ll)> DFS=[&](ll x){
		if(dvis[x]) return;
		dvis[x]=1;
		book[x]=1;
		subt[x]=1;	//子树大小初始化为 1
		for(auto it:son[x]){
			DFS(it);
			if(!ring[it]) subt[x]+=subt[it];	//对于环上的点，不计入贡献（本来就在正常循环内）
		}
	};
	
	for(ll i=1;i<=n;i++) cin>>r[i],son[r[i]].emplace_back(i);
	for(ll i=1;i<=n;i++){
		if(book[i]) continue;
		ll cur=i;
		while(!book[cur]){
			book[cur]+=1;
			cur=r[cur];
		}
		while(!ring[cur]){
			ring[cur]=1;
			cur=r[cur];
		}
		DFS(cur);
	}
	
//	for(ll i=1;i<=n;i++)
//		if(ring[i]){
//			subt[i]=0;
//			for(ll it:son[i])
//				subt[i]=max(subt[i],ring[it]?0:subt[it]);
//		}
	
	ll ans=0;
//	OOO for(ll i=1;i<=n;i++) cout<<subt[i]<<" \n"[i==n];
	for(ll i=1;i<=n;i++)
		ans=max(ans,(ring[i]?0:subt[i])+2);
//	OOO
	cout<<ans<<endl;
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
